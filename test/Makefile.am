LDADD = -lassemblyline
AM_LDFLAGS = -L$(top_srcdir)/src
AM_CPPFLAGS = -I$(top_srcdir)/src/
AM_CFLAGS = -Wall -std=gnu99

# runner for 'asm'-tests
ASM_LOG_COMPILER = ./al_nasm_compare.sh
# build this program (takes asm file, uses assemblyline
# to assemble and outputs linewise hex of machinecode)


# add .c -tests here
TEST_C= check_chunk_counting \
		invalid \
		memory_reallocation \
		run \
		jump

TEST_EXTENSIONS = .asm

# add .asm-tests here
TEST_ASM =\
		  and.asm \
		  adcx.asm \
		  add.asm \
		  adox.asm \
		  bzhi.asm \
		  clc.asm \
		  imul.asm \
		  lea.asm \
		  mov.asm \
		  movntdqa.asm \
		  movntq.asm \
		  movzx.asm \
		  mulx.asm \
		  negative_mem_disp.asm \
		  new_instruction.asm \
		  nop.asm \
		  not.asm \
		  or.asm \
		  rorx.asm \
		  sarx.asm \
		  setc.asm \
		  seto.asm \
		  shl.asm \
		  shlx.asm \
		  shr.asm \
		  shrd.asm \
		  shrx.asm \
		  sub.asm \
		  xor.asm \
		  zero_byte_rbp.asm

# if needed, add utility programs, which should be build for the test, to check_PROGRAMS
check_PROGRAMS = asm_to_stdout $(TEST_C)
TESTS = $(TEST_ASM) $(TEST_C)

# maybe this is helpful to create testcases:
# R='rax rbx rcx rdx rdi r8 r9 r10 r11 r12 r13 r14 r15 rsp rsi rbp';
# for a in `echo $R`; do for b in $(echo $R); do for c in $(echo $R); do echo "shlx $a, $b, $c" >> shlx.asm; done ; done; done
#
# R='al cl dl bl spl bpl sil dil r8b r9b r10b r11b r12b r13b r14b r15b';
# for a in `echo $R`; do echo "setc $a" >> setc.asm; done
