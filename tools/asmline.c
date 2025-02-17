/**
 * Copyright 2021 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*command-tool for generating machine code from a x64 assembly file*/
#include <assemblyline.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_print_usage(char *error_msg) {
  fprintf(
      stderr,
      "%s\n\nUSAGE:\n\tasmline [-r] [-p] [-c CHUNK_SIZE>1] [-o "
      "ELF_FILENAME_NO_EXT] path/to/file.asm\n\nDESCRIPTION:\n\tGenerates "
      "machine code from a x64 assembly file. Machine code could be "
      "executed directly without the need of an executable file format.\n "
      "\tObtain command line instructions for generating a ELF binary file "
      "from assembly code.\n\n"
      "OPTIONS:\n\t"
      "-r --return\n"
      "\t\tExecutes assembly code and prints out the contents of the rax "
      "register (return register)\n\n"
      "\t-p --print\n"
      "\t\tWhen assembling path/to/file.asm the corresponding machine code "
      "will be printed to stdout.\n\n"
      "\t-c --chunk CHUNK_SIZE>1\n"
      "\t\tSets a given CHUNK_SIZE boundary in bytes. Nop padding will be used "
      "to ensure no instruction\n"
      "\t\topcode will cross the specified CHUNK_SIZE "
      "boundary.\n\n"
      "\t-o --object FILENAME\n"
      "\t\tGenerates a binary file from path/to/file.asm called "
      "FILENAME.bin in the current directory.\n",
      error_msg);
  exit(EXIT_FAILURE);
}

int check_digit(char *optarg) {
  int len = strlen(optarg);
  for (int i = 0; i < len; i++)
    if (optarg[i] < '0' || optarg[i] > '9')
      return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int create_bin_file(assemblyline_t al, char *file_name) {

  FILE *write_ptr = fopen(strcat(file_name, ".bin"), "wb");

  if (write_ptr == NULL)
    return EXIT_FAILURE;

  fwrite(asm_get_buffer(al), sizeof(uint8_t), asm_get_offset(al), write_ptr);
  fclose(write_ptr);

  return EXIT_SUCCESS;
}

void execute_get_ret_value(int (*exe)()) {
  printf("\nthe value is 0x%x\n", ((int (*)())exe)());
}

int main(int argc, char *argv[]) {

  int opt, get_ret = 0, create_bin = 0;
  int chunk_size;
  char *write_file = NULL;

  static struct option long_options[] = {/* These options set a flag. */
                                         {"help", no_argument, 0, 'h'},
                                         {"return", no_argument, 0, 'r'},
                                         {"print", no_argument, 0, 'p'},
                                         {"chunk", required_argument, 0, 'c'},
                                         {"object", required_argument, 0, 'o'},
                                         {0, 0, 0, 0}};

  /* getopt_long stores the option index here. */
  int option_index = 0;

  if (argc < 2 && isatty(fileno(stdin)))
    err_print_usage("Error: invalid number of arguments");

  assemblyline_t al = asm_create_instance(NULL, 0);
  while ((opt = getopt_long(argc, argv, "hrpc:o:", long_options,
                            &option_index)) != -1) {
    switch (opt) {
    case 'h':
      err_print_usage("");
      break;
    case 'r':
      get_ret = 1;
      break;
    case 'p':
      asm_set_debug(al, true);
      break;
    case 'c':
      if (check_digit(optarg))
        err_print_usage("Error: [-c CHUNK_SIZE>1] expects an integer");
      chunk_size = atoi(optarg);
      asm_set_chunk_size(al, chunk_size);
      break;
    case 'o':
      if (strchr(optarg, '.'))
        err_print_usage("elf filename cannot have an extension");
      create_bin = 1;
      write_file = optarg;
      break;

    default: /* '?' */
      err_print_usage("Error: invalid option");
    }
  }

  if (optind >= argc) {
    // check is stdin is provided via pipe
    if (!isatty(fileno(stdin))) {
      char *line = NULL;
      size_t size = 100;
      while (getline(&line, &size, stdin) != -1) {
        if (assemble_str(al, line) == EXIT_FAILURE) {
          fprintf(stderr, "failed to assemble instruction: %s\n", line);
          exit(EXIT_FAILURE);
        }
      }
      free(line);
    } else {
      err_print_usage("Error: Expected path/to/file.asm after options");
    }
  } else {
    if (assemble_file(al, argv[optind]) == EXIT_FAILURE) {
      fprintf(stderr, "failed to assemble file: %s\n", argv[optind]);
      exit(EXIT_FAILURE);
    }
  }

  if (get_ret) {
    int (*funcB)() = (int (*)())(asm_get_code(al));
    execute_get_ret_value(funcB);
  }

  if (create_bin) {
    if (create_bin_file(al, write_file) == EXIT_FAILURE) {
      fprintf(stderr, "failed to create test.bin\n");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
