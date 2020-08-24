# mark_description "Intel(R) C++ Intel(R) 64 Compiler for applications running on Intel(R) 64, Version 19.1.1.217 Build 20200306";
# mark_description "";
# mark_description "-I/opt/intel/mkl/include -O3 -qopenmp -L/opt/intel/mkl/lib/intel64 -lmkl_intel_ilp64 -lmkl_intel_thread -lmk";
# mark_description "l_core -ldl -lm -lpthread -qopt-report=5 -qopt-report-phase=vec -std=c++11 -march=native -mtune=native -DSQU";
# mark_description "EEZE_USE_MKL -S";
	.file "test_blas.cc"
	.text
..TXTST0:
.L_2__routine_start_main_0:
# -- Begin  main, L_main_19__par_region0_2.4
	.text
# mark_begin;
       .align    16,0x90
	.globl main
# --- main()
main:
..B1.1:                         # Preds ..B1.0
                                # Execution count [0.00e+00]
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0xb, main$$LSDA
..___tag_value_main.7:
..L8:
                                                          #9.12
        pushq     %rbp                                          #9.12
	.cfi_def_cfa_offset 16
        movq      %rsp, %rbp                                    #9.12
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        andq      $-128, %rsp                                   #9.12
        subq      $256, %rsp                                    #9.12
        movl      $3, %edi                                      #9.12
        xorl      %esi, %esi                                    #9.12
        movq      %rbx, 136(%rsp)                               #9.12[spill]
        movq      %r15, 104(%rsp)                               #9.12[spill]
        movq      %r14, 112(%rsp)                               #9.12[spill]
        movq      %r13, 120(%rsp)                               #9.12[spill]
        movq      %r12, 128(%rsp)                               #9.12[spill]
        call      __intel_new_feature_proc_init                 #9.12
	.cfi_escape 0x10, 0x03, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x88, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0c, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0d, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x78, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0e, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x70, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0f, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x68, 0xff, 0xff, 0xff, 0x22
                                # LOE
..B1.124:                       # Preds ..B1.1
                                # Execution count [0.00e+00]
        vstmxcsr  (%rsp)                                        #9.12
        movl      $.2.73_2_kmpc_loc_struct_pack.217, %edi       #9.12
        xorl      %esi, %esi                                    #9.12
        orl       $32832, (%rsp)                                #9.12
        xorl      %eax, %eax                                    #9.12
        vldmxcsr  (%rsp)                                        #9.12
..___tag_value_main.22:
        call      __kmpc_begin                                  #9.12
..___tag_value_main.23:
                                # LOE
..B1.2:                         # Preds ..B1.124
                                # Execution count [1.00e+00]
        movl      $4194304, %edi                                #57.10
        movl      $32, %esi                                     #57.10
        xorl      %ebx, %ebx                                    #564.3
        movq      %rbx, 64(%rsp)                                #11.17
        movq      %rbx, 72(%rsp)                                #11.17
..___tag_value_main.24:
#       MKL_malloc(size_t, int)
        call      MKL_malloc                                    #57.10
..___tag_value_main.25:
                                # LOE rax rbx
..B1.4:                         # Preds ..B1.2
                                # Execution count [2.82e-01]
        testq     %rax, %rax                                    #194.17
        je        ..B1.113      # Prob 1%                       #194.17
                                # LOE rax rbx
..B1.5:                         # Preds ..B1.4
                                # Execution count [1.00e+00]
        movl      $4194304, %edi                                #57.10
        movl      $32, %esi                                     #57.10
        movq      %rax, 64(%rsp)                                #11.17
        movq      $1048576, 72(%rsp)                            #11.17
        movq      %rbx, 80(%rsp)                                #11.26
        movq      %rbx, 88(%rsp)                                #11.26
..___tag_value_main.26:
#       MKL_malloc(size_t, int)
        call      MKL_malloc                                    #57.10
..___tag_value_main.27:
                                # LOE rax rbx
..B1.7:                         # Preds ..B1.5
                                # Execution count [2.82e-01]
        testq     %rax, %rax                                    #194.17
        je        ..B1.108      # Prob 1%                       #194.17
                                # LOE rax rbx
..B1.8:                         # Preds ..B1.7
                                # Execution count [1.00e+00]
        xorl      %edi, %edi                                    #13.45
        movq      %rax, 80(%rsp)                                #11.26
        movq      $1048576, 88(%rsp)                            #11.26
#       time(time_t *)
        call      time                                          #13.45
                                # LOE rax rbx
..B1.9:                         # Preds ..B1.8
                                # Execution count [1.00e+00]
        movl      $13631488, %esi                               #13.3
        lea       144(%rsp), %rdi                               #13.3
        movl      %eax, %edx                                    #13.3
..___tag_value_main.28:
#       vslNewStream(VSLStreamStatePtr *, int, unsigned int)
        call      vslNewStream                                  #13.3
..___tag_value_main.29:
                                # LOE rbx
..B1.11:                        # Preds ..B1.9
                                # Execution count [1.00e+00]
        xorl      %edi, %edi                                    #14.3
        vmovss    .L_2il0floatpacket.5(%rip), %xmm1             #14.3
        movl      $1048576, %edx                                #14.3
        vxorps    %xmm0, %xmm0, %xmm0                           #14.3
        movq      144(%rsp), %rsi                               #14.3
        movq      64(%rsp), %rcx                                #14.3
..___tag_value_main.30:
#       vsRngUniform(int, VSLStreamStatePtr, int, float *, float, float)
        call      vsRngUniform                                  #14.3
..___tag_value_main.31:
                                # LOE rbx
..B1.13:                        # Preds ..B1.11
                                # Execution count [1.00e+00]
        xorl      %edi, %edi                                    #16.3
        vmovss    .L_2il0floatpacket.5(%rip), %xmm1             #16.3
        movl      $1048576, %edx                                #16.3
        vxorps    %xmm0, %xmm0, %xmm0                           #16.3
        movq      144(%rsp), %rsi                               #16.3
        movq      80(%rsp), %rcx                                #16.3
..___tag_value_main.32:
#       vsRngUniform(int, VSLStreamStatePtr, int, float *, float, float)
        call      vsRngUniform                                  #16.3
..___tag_value_main.33:
                                # LOE rbx
..B1.15:                        # Preds ..B1.13
                                # Execution count [1.00e+00]
        lea       144(%rsp), %rdi                               #18.3
..___tag_value_main.34:
#       vslDeleteStream(VSLStreamStatePtr *)
        call      vslDeleteStream                               #18.3
..___tag_value_main.35:
                                # LOE rbx
..B1.17:                        # Preds ..B1.15
                                # Execution count [1.00e+00]
        movq      64(%rsp), %rax                                #26.13
        movl      $_ZSt4cout, %edi                              #26.13
        movq      80(%rsp), %rdx                                #26.13
        vmovss    .L_2il0floatpacket.6(%rip), %xmm0             #26.13
        vmovss    4096(%rax), %xmm1                             #26.13
        vfmadd213ss 4096(%rdx), %xmm1, %xmm0                    #26.13
..___tag_value_main.36:
#       std::basic_ostream<char, std::char_traits<char>>::operator<<(std::basic_ostream<char, std::char_traits<char>> *, float)
        call      _ZNSolsEf                                     #26.13
..___tag_value_main.37:
                                # LOE rax rbx
..B1.19:                        # Preds ..B1.17
                                # Execution count [1.00e+00]
        movq      %rax, %rdi                                    #26.44
        movl      $_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi #26.44
..___tag_value_main.38:
#       std::basic_ostream<char, std::char_traits<char>>::operator<<(std::basic_ostream<char, std::char_traits<char>> *, std::basic_ostream<char, std::char_traits<char>>::__ostream_type &(*)(std::basic_ostream<char, std::char_traits<char>>::__ostream_type &))
        call      _ZNSolsEPFRSoS_E                              #26.44
..___tag_value_main.39:
                                # LOE rbx
..B1.21:                        # Preds ..B1.19
                                # Execution count [1.00e+00]
        movq      72(%rsp), %rdi                                #27.11
        lea       64(%rsp), %rax                                #27.11
        movq      %rdi, -48(%rax)                               #27.3
        lea       100(%rsp), %rdx                               #27.18
        movq      24(%rax), %rdi                                #27.3
        lea       80(%rsp), %r8                                 #27.3
        movl      $2, 36(%rax)                                  #27.18
        lea       16(%rsp), %rcx                                #27.11
        movq      %rax, -40(%rax)                               #27.3
        lea       40(%rsp), %rsi                                #638.17
        movq      %rdx, -32(%rax)                               #27.3
        lea       (,%rdi,4), %r9                                #12.21
        movq      %rdi, -24(%rax)                               #638.12
        movq      %r8, -16(%rax)                                #638.12
        movq      %rcx, -8(%rax)                                #638.12
        movq      %rsi, 88(%rax)                                #11.7
        movq      %r8, 96(%rax)                                 #11.7
        cmpq      $131072, %r9                                  #13.9
        jae       ..B1.51       # Prob 50%                      #13.9
                                # LOE rbx rdi r9
..B1.22:                        # Preds ..B1.21
                                # Execution count [5.00e-01]
        testq     %rdi, %rdi                                    #14.30
        jle       ..B1.57       # Prob 50%                      #14.30
                                # LOE rbx rdi r9
..B1.23:                        # Preds ..B1.22
                                # Execution count [0.00e+00]
        movq      56(%rsp), %rax                                #638.17
        movq      48(%rsp), %rsi                                #638.17
        movq      8(%rax), %rdx                                 #337.18
        movq      16(%rax), %rcx                                #337.26
        movq      (%rsi), %rsi                                  #731.14
        movq      (%rdx), %rax                                  #731.14
        movl      (%rcx), %ecx                                  #208.55
        movq      80(%rsp), %rdx                                #27.3
        cmpq      $6, %rdi                                      #14.30
        jle       ..B1.45       # Prob 50%                      #14.30
                                # LOE rax rdx rbx rsi rdi r9 ecx
..B1.24:                        # Preds ..B1.23
                                # Execution count [0.00e+00]
        movq      %rdx, %r8                                     #208.51
        subq      %rax, %r8                                     #208.51
        cmpq      %r9, %r8                                      #14.30
        jge       ..B1.26       # Prob 50%                      #14.30
                                # LOE rax rdx rbx rsi rdi r8 r9 ecx
..B1.25:                        # Preds ..B1.24
                                # Execution count [0.00e+00]
        negq      %r8                                           #15.9
        cmpq      %r9, %r8                                      #14.30
        jl        ..B1.45       # Prob 50%                      #14.30
                                # LOE rax rdx rbx rsi rdi r9 ecx
..B1.26:                        # Preds ..B1.24 ..B1.25
                                # Execution count [0.00e+00]
        movq      %rdx, %r8                                     #190.51
        subq      %rsi, %r8                                     #190.51
        cmpq      %r9, %r8                                      #14.30
        jge       ..B1.28       # Prob 50%                      #14.30
                                # LOE rax rdx rbx rsi rdi r8 r9 ecx
..B1.27:                        # Preds ..B1.26
                                # Execution count [0.00e+00]
        negq      %r8                                           #15.9
        cmpq      %r9, %r8                                      #14.30
        jl        ..B1.45       # Prob 50%                      #14.30
                                # LOE rax rdx rbx rsi rdi ecx
..B1.28:                        # Preds ..B1.26 ..B1.27
                                # Execution count [2.25e-01]
        cmpq      $8, %rdi                                      #14.30
        jl        ..B1.92       # Prob 10%                      #14.30
                                # LOE rax rdx rbx rsi rdi ecx
..B1.29:                        # Preds ..B1.28
                                # Execution count [2.25e-01]
        cmpq      $381, %rdi                                    #14.30
        jl        ..B1.94       # Prob 10%                      #14.30
                                # LOE rax rdx rbx rsi rdi ecx
..B1.30:                        # Preds ..B1.29
                                # Execution count [2.25e-01]
        movq      %rdx, %r9                                     #14.30
        andq      $31, %r9                                      #14.30
        je        ..B1.33       # Prob 50%                      #14.30
                                # LOE rax rdx rbx rsi rdi r9 ecx
..B1.31:                        # Preds ..B1.30
                                # Execution count [2.25e-01]
        testq     $3, %r9                                       #14.30
        jne       ..B1.92       # Prob 10%                      #14.30
                                # LOE rax rdx rbx rsi rdi r9 ecx
..B1.32:                        # Preds ..B1.31
                                # Execution count [1.13e-01]
        negq      %r9                                           #14.30
        addq      $32, %r9                                      #14.30
        shrq      $2, %r9                                       #14.30
                                # LOE rax rdx rbx rsi rdi r9 ecx
..B1.33:                        # Preds ..B1.32 ..B1.30
                                # Execution count [2.25e-01]
        lea       8(%r9), %r8                                   #14.30
        cmpq      %r8, %rdi                                     #14.30
        jl        ..B1.92       # Prob 10%                      #14.30
                                # LOE rax rdx rbx rsi rdi r9 ecx
..B1.34:                        # Preds ..B1.33
                                # Execution count [2.50e-01]
        movq      %rdi, %r8                                     #14.30
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        subq      %r9, %r8                                      #14.30
        andq      $7, %r8                                       #14.30
        negq      %r8                                           #14.30
        addq      %rdi, %r8                                     #14.30
        vcvtsi2ss %ecx, %xmm0, %xmm0                            #208.55
        testq     %r9, %r9                                      #14.30
        jbe       ..B1.38       # Prob 9%                       #14.30
                                # LOE rax rdx rbx rsi rdi r8 r9 ecx xmm0
..B1.36:                        # Preds ..B1.34 ..B1.36
                                # Execution count [1.25e+00]
        vmovss    (%rax,%rbx,4), %xmm1                          #208.51
        vfmadd213ss (%rsi,%rbx,4), %xmm0, %xmm1                 #15.9
        vmovss    %xmm1, (%rdx,%rbx,4)                          #15.9
        incq      %rbx                                          #14.30
        cmpq      %r9, %rbx                                     #14.30
        jb        ..B1.36       # Prob 82%                      #14.30
                                # LOE rax rdx rbx rsi rdi r8 r9 ecx xmm0
..B1.38:                        # Preds ..B1.36 ..B1.34 ..B1.94
                                # Execution count [2.25e-01]
        vbroadcastss %xmm0, %ymm0                               #208.55
                                # LOE rax rdx rsi rdi r8 r9 ecx ymm0
..B1.39:                        # Preds ..B1.39 ..B1.38
                                # Execution count [1.25e+00]
        vmovups   (%rax,%r9,4), %ymm1                           #208.51
        vfmadd213ps (%rsi,%r9,4), %ymm0, %ymm1                  #190.55
        vmovups   %ymm1, (%rdx,%r9,4)                           #15.9
        addq      $8, %r9                                       #14.30
        cmpq      %r8, %r9                                      #14.30
        jb        ..B1.39       # Prob 82%                      #14.30
                                # LOE rax rdx rsi rdi r8 r9 ecx ymm0
..B1.41:                        # Preds ..B1.39 ..B1.92
                                # Execution count [2.50e-01]
        cmpq      %rdi, %r8                                     #14.30
        jae       ..B1.58       # Prob 9%                       #14.30
                                # LOE rax rdx rsi rdi r8 ecx
..B1.42:                        # Preds ..B1.41
                                # Execution count [2.25e-01]
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        vcvtsi2ss %ecx, %xmm0, %xmm0                            #208.55
                                # LOE rax rdx rsi rdi r8 xmm0
..B1.43:                        # Preds ..B1.43 ..B1.42
                                # Execution count [1.25e+00]
        vmovss    (%rax,%r8,4), %xmm1                           #208.51
        vfmadd213ss (%rsi,%r8,4), %xmm0, %xmm1                  #15.9
        vmovss    %xmm1, (%rdx,%r8,4)                           #15.9
        incq      %r8                                           #14.30
        cmpq      %rdi, %r8                                     #14.30
        jb        ..B1.43       # Prob 82%                      #14.30
        jmp       ..B1.58       # Prob 100%                     #14.30
                                # LOE rax rdx rsi rdi r8 xmm0
..B1.45:                        # Preds ..B1.23 ..B1.27 ..B1.25
                                # Execution count [2.50e-01]
        movq      %rdi, %r8                                     #14.30
        movl      $1, %r9d                                      #14.30
        shrq      $1, %r8                                       #14.30
        je        ..B1.49       # Prob 9%                       #14.30
                                # LOE rax rdx rbx rsi rdi r8 r9 ecx
..B1.46:                        # Preds ..B1.45
                                # Execution count [2.25e-01]
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        vcvtsi2ss %ecx, %xmm0, %xmm0                            #208.55
                                # LOE rax rdx rbx rsi rdi r8 ecx xmm0
..B1.47:                        # Preds ..B1.47 ..B1.46
                                # Execution count [6.25e-01]
        vmovss    (%rax,%rbx,8), %xmm1                          #208.51
        vfmadd213ss (%rsi,%rbx,8), %xmm0, %xmm1                 #15.9
        vmovss    %xmm1, (%rdx,%rbx,8)                          #15.9
        vmovss    4(%rax,%rbx,8), %xmm2                         #208.51
        vfmadd213ss 4(%rsi,%rbx,8), %xmm0, %xmm2                #15.9
        vmovss    %xmm2, 4(%rdx,%rbx,8)                         #15.9
        incq      %rbx                                          #14.30
        cmpq      %r8, %rbx                                     #14.30
        jb        ..B1.47       # Prob 63%                      #14.30
                                # LOE rax rdx rbx rsi rdi r8 ecx xmm0
..B1.48:                        # Preds ..B1.47
                                # Execution count [2.25e-01]
        lea       1(%rbx,%rbx), %r9                             #15.9
                                # LOE rax rdx rsi rdi r9 ecx
..B1.49:                        # Preds ..B1.48 ..B1.45
                                # Execution count [2.50e-01]
        decq      %r9                                           #14.30
        cmpq      %rdi, %r9                                     #14.30
        jae       ..B1.58       # Prob 9%                       #14.30
                                # LOE rax rdx rsi r9 ecx
..B1.50:                        # Preds ..B1.49
                                # Execution count [2.25e-01]
        vxorps    %xmm1, %xmm1, %xmm1                           #208.55
        vcvtsi2ss %ecx, %xmm1, %xmm1                            #208.55
        vmovss    (%rax,%r9,4), %xmm0                           #208.51
        vfmadd213ss (%rsi,%r9,4), %xmm0, %xmm1                  #15.9
        vmovss    %xmm1, (%rdx,%r9,4)                           #15.9
        jmp       ..B1.58       # Prob 100%                     #15.9
                                # LOE rdx
..B1.51:                        # Preds ..B1.21
                                # Execution count [5.00e-01]
        movl      $.2.73_2_kmpc_loc_struct_pack.228, %edi       #19.5
        call      __kmpc_global_thread_num                      #19.5
                                # LOE eax
..B1.127:                       # Preds ..B1.51
                                # Execution count [5.00e-01]
        movl      %eax, 96(%rsp)                                #19.5
        movl      $.2.73_2_kmpc_loc_struct_pack.294, %edi       #19.5
        xorl      %eax, %eax                                    #19.5
..___tag_value_main.40:
        call      __kmpc_ok_to_fork                             #19.5
..___tag_value_main.41:
                                # LOE eax
..B1.52:                        # Preds ..B1.127
                                # Execution count [5.00e-01]
        testl     %eax, %eax                                    #19.5
        je        ..B1.54       # Prob 50%                      #19.5
                                # LOE
..B1.53:                        # Preds ..B1.52
                                # Execution count [0.00e+00]
        movl      $L_main_19__par_region0_2.4, %edx             #19.5
        lea       152(%rsp), %rcx                               #19.5
        movl      $.2.73_2_kmpc_loc_struct_pack.294, %edi       #19.5
        lea       8(%rcx), %r8                                  #19.5
        movl      $3, %esi                                      #19.5
        lea       8(%rsp), %r9                                  #19.5
        xorl      %eax, %eax                                    #19.5
..___tag_value_main.42:
        call      __kmpc_fork_call                              #19.5
..___tag_value_main.43:
        jmp       ..B1.57       # Prob 100%                     #19.5
                                # LOE
..B1.54:                        # Preds ..B1.52
                                # Execution count [0.00e+00]
        movl      $.2.73_2_kmpc_loc_struct_pack.294, %edi       #19.5
        xorl      %eax, %eax                                    #19.5
        movl      96(%rsp), %esi                                #19.5
..___tag_value_main.44:
        call      __kmpc_serialized_parallel                    #19.5
..___tag_value_main.45:
                                # LOE
..B1.55:                        # Preds ..B1.54
                                # Execution count [0.00e+00]
        movl      $___kmpv_zeromain_0, %esi                     #19.5
        lea       96(%rsp), %rdi                                #19.5
        lea       56(%rdi), %rdx                                #19.5
        lea       8(%rdx), %rcx                                 #19.5
        lea       -88(%rdi), %r8                                #19.5
..___tag_value_main.46:
        call      L_main_19__par_region0_2.4                    #19.5
..___tag_value_main.47:
                                # LOE
..B1.56:                        # Preds ..B1.55
                                # Execution count [0.00e+00]
        movl      $.2.73_2_kmpc_loc_struct_pack.294, %edi       #19.5
        xorl      %eax, %eax                                    #19.5
        movl      96(%rsp), %esi                                #19.5
..___tag_value_main.48:
        call      __kmpc_end_serialized_parallel                #19.5
..___tag_value_main.49:
                                # LOE
..B1.57:                        # Preds ..B1.22 ..B1.53 ..B1.56
                                # Execution count [5.00e-01]
        movq      80(%rsp), %rdx                                #16.3
                                # LOE rdx
..B1.58:                        # Preds ..B1.43 ..B1.41 ..B1.49 ..B1.50 ..B1.57
                                #      
                                # Execution count [1.00e+00]
        vmovss    4096(%rdx), %xmm0                             #31.13
        movl      $_ZSt4cout, %edi                              #31.13
        vzeroupper                                              #31.13
        vmovss    4096(%rdx), %xmm0                             #31.13
..___tag_value_main.50:
#       std::basic_ostream<char, std::char_traits<char>>::operator<<(std::basic_ostream<char, std::char_traits<char>> *, float)
        call      _ZNSolsEf                                     #31.13
..___tag_value_main.51:
                                # LOE rax
..B1.60:                        # Preds ..B1.58
                                # Execution count [1.00e+00]
        movq      %rax, %rdi                                    #31.27
        movl      $_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi #31.27
..___tag_value_main.52:
#       std::basic_ostream<char, std::char_traits<char>>::operator<<(std::basic_ostream<char, std::char_traits<char>> *, std::basic_ostream<char, std::char_traits<char>>::__ostream_type &(*)(std::basic_ostream<char, std::char_traits<char>>::__ostream_type &))
        call      _ZNSolsEPFRSoS_E                              #31.27
..___tag_value_main.53:
                                # LOE
..B1.62:                        # Preds ..B1.60
                                # Execution count [1.00e+00]
        movq      80(%rsp), %rdi                                #31.27
        testq     %rdi, %rdi                                    #61.14
        je        ..B1.64       # Prob 15%                      #61.14
                                # LOE rdi
..B1.63:                        # Preds ..B1.62
                                # Execution count [8.42e-01]
..___tag_value_main.54:
#       MKL_free(void *)
        call      MKL_free                                      #61.23
..___tag_value_main.55:
                                # LOE
..B1.64:                        # Preds ..B1.62 ..B1.63
                                # Execution count [1.00e+00]
        movq      64(%rsp), %rdi                                #31.27
        testq     %rdi, %rdi                                    #61.14
        je        ..B1.66       # Prob 15%                      #61.14
                                # LOE rdi
..B1.65:                        # Preds ..B1.64
                                # Execution count [8.42e-01]
..___tag_value_main.56:
#       MKL_free(void *)
        call      MKL_free                                      #61.23
..___tag_value_main.57:
                                # LOE
..B1.66:                        # Preds ..B1.64 ..B1.65
                                # Execution count [1.00e+00]
        movl      $.2.73_2_kmpc_loc_struct_pack.236, %edi       #32.1
        xorl      %eax, %eax                                    #32.1
..___tag_value_main.58:
        call      __kmpc_end                                    #32.1
..___tag_value_main.59:
                                # LOE
..B1.67:                        # Preds ..B1.66
                                # Execution count [1.00e+00]
        movq      104(%rsp), %r15                               #32.1[spill]
	.cfi_restore 15
        xorl      %eax, %eax                                    #32.1
        movq      112(%rsp), %r14                               #32.1[spill]
	.cfi_restore 14
        movq      120(%rsp), %r13                               #32.1[spill]
	.cfi_restore 13
        movq      128(%rsp), %r12                               #32.1[spill]
	.cfi_restore 12
        movq      136(%rsp), %rbx                               #32.1[spill]
	.cfi_restore 3
        movq      %rbp, %rsp                                    #32.1
        popq      %rbp                                          #32.1
	.cfi_def_cfa 7, 8
	.cfi_restore 6
        ret                                                     #32.1
	.cfi_def_cfa 6, 16
                                # LOE
L_main_19__par_region0_2.4:
# parameter 1: %rdi
# parameter 2: %rsi
# parameter 3: %rdx
# parameter 4: %rcx
# parameter 5: %r8
..B1.68:                        # Preds ..B1.0
                                # Execution count [5.00e-01]
        pushq     %rbp                                          #19.5
	.cfi_def_cfa 7, 16
        movq      %rsp, %rbp                                    #19.5
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        andq      $-128, %rsp                                   #19.5
        subq      $256, %rsp                                    #19.5
        movq      %rbx, 136(%rsp)                               #19.5[spill]
	.cfi_escape 0x10, 0x03, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x88, 0xff, 0xff, 0xff, 0x22
        movq      (%rdx), %rbx                                  #20.16
        movq      %r13, 120(%rsp)                               #19.5[spill]
        movq      %r14, 112(%rsp)                               #19.5[spill]
	.cfi_escape 0x10, 0x0d, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x78, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0e, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x70, 0xff, 0xff, 0xff, 0x22
        movq      (%rbx), %r13                                  #238.59
        movq      %r15, 104(%rsp)                               #19.5[spill]
        movq      %r12, 128(%rsp)                               #19.5[spill]
	.cfi_escape 0x10, 0x0c, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0f, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x68, 0xff, 0xff, 0xff, 0x22
        movq      %rcx, %r12                                    #19.5
        movl      (%rdi), %r14d                                 #19.5
        testq     %r13, %r13                                    #20.5
        jle       ..B1.91       # Prob 50%                      #20.5
                                # LOE rbx r12 r13 r14d
..B1.69:                        # Preds ..B1.68
                                # Execution count [2.50e-01]
        jbe       ..B1.91       # Prob 10%                      #20.5
                                # LOE rbx r12 r13 r14d
..B1.70:                        # Preds ..B1.69
                                # Execution count [1.25e+00]
        decq      %r13                                          #19.5
        movl      $1, %r10d                                     #19.5
        movq      $0, (%rsp)                                    #19.5
        movl      $.2.73_2_kmpc_loc_struct_pack.274, %edi       #19.5
        movq      %r13, 8(%rsp)                                 #19.5
        movl      %r14d, %esi                                   #19.5
        movl      $0, 24(%rsp)                                  #19.5
        movl      $34, %edx                                     #19.5
        movq      %r10, 16(%rsp)                                #19.5
        addq      $-32, %rsp                                    #19.5
	.cfi_escape 0x2e, 0x20
        lea       56(%rsp), %rcx                                #19.5
        lea       32(%rsp), %r8                                 #19.5
        lea       40(%rsp), %r9                                 #19.5
        lea       48(%rsp), %rax                                #19.5
        movq      %rax, (%rsp)                                  #19.5
        movq      %r10, 8(%rsp)                                 #19.5
        movq      %r10, 16(%rsp)                                #19.5
        call      __kmpc_for_static_init_8u                     #19.5
                                # LOE rbx r12 r13 r14d
..B1.128:                       # Preds ..B1.70
                                # Execution count [1.25e+00]
        addq      $32, %rsp                                     #19.5
	.cfi_escape 0x2e, 0x00
                                # LOE rbx r12 r13 r14d
..B1.71:                        # Preds ..B1.128
                                # Execution count [0.00e+00]
        movq      (%rsp), %r8                                   #19.5
        movq      8(%rsp), %rax                                 #19.5
        cmpq      %r13, %r8                                     #19.5
        ja        ..B1.90       # Prob 50%                      #19.5
                                # LOE rax rbx r8 r12 r13 r14d
..B1.72:                        # Preds ..B1.71
                                # Execution count [1.25e+00]
        cmpq      %r13, %rax                                    #19.5
        cmovb     %rax, %r13                                    #19.5
        cmpq      %r13, %r8                                     #20.5
        ja        ..B1.90       # Prob 50%                      #20.5
                                # LOE rbx r8 r12 r13 r14d
..B1.73:                        # Preds ..B1.72
                                # Execution count [2.25e-01]
        movq      8(%rbx), %rdi                                 #299.18
        subq      %r8, %r13                                     #19.5
        movq      16(%rbx), %rbx                                #299.27
        incq      %r13                                          #19.5
        movq      (%r12), %rcx                                  #21.7
        movq      (%rdi), %rdi                                  #731.14
        movq      8(%rbx), %rax                                 #337.18
        movq      16(%rbx), %rdx                                #337.26
        movq      (%rax), %rbx                                  #731.14
        movl      (%rdx), %edx                                  #208.55
        movq      (%rcx), %rax                                  #739.14
        cmpq      $16, %r13                                     #19.5
        jb        ..B1.118      # Prob 10%                      #19.5
                                # LOE rax rbx rdi r8 r13 edx r14d
..B1.74:                        # Preds ..B1.73
                                # Execution count [2.25e-01]
        lea       (%rax,%r8,4), %r15                            #21.9
        cmpq      $29, %r13                                     #19.5
        jb        ..B1.120      # Prob 10%                      #19.5
                                # LOE rax rbx rdi r8 r13 r15 edx r14d
..B1.75:                        # Preds ..B1.74
                                # Execution count [2.25e-01]
        movq      %r15, %r12                                    #19.5
        andq      $31, %r12                                     #19.5
        je        ..B1.78       # Prob 50%                      #19.5
                                # LOE rax rbx rdi r8 r12 r13 r15 edx r14d
..B1.76:                        # Preds ..B1.75
                                # Execution count [2.25e-01]
        testq     $3, %r12                                      #19.5
        jne       ..B1.118      # Prob 10%                      #19.5
                                # LOE rax rbx rdi r8 r12 r13 r15 edx r14d
..B1.77:                        # Preds ..B1.76
                                # Execution count [1.13e-01]
        negq      %r12                                          #19.5
        addq      $32, %r12                                     #19.5
        shrq      $2, %r12                                      #19.5
                                # LOE rax rbx rdi r8 r12 r13 r15 edx r14d
..B1.78:                        # Preds ..B1.77 ..B1.75
                                # Execution count [2.25e-01]
        lea       16(%r12), %rcx                                #19.5
        cmpq      %rcx, %r13                                    #19.5
        jb        ..B1.118      # Prob 10%                      #19.5
                                # LOE rax rbx rdi r8 r12 r13 r15 edx r14d
..B1.79:                        # Preds ..B1.78
                                # Execution count [2.25e-01]
        movq      %r13, %rcx                                    #19.5
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        subq      %r12, %rcx                                    #19.5
        xorl      %r11d, %r11d                                  #19.5
        andq      $15, %rcx                                     #19.5
        lea       (%rbx,%r8,4), %r10                            #208.51
        negq      %rcx                                          #19.5
        lea       (%rdi,%r8,4), %r9                             #190.51
        addq      %r13, %rcx                                    #19.5
        vcvtsi2ss %edx, %xmm0, %xmm0                            #208.55
        testq     %r12, %r12                                    #19.5
        jbe       ..B1.83       # Prob 0%                       #19.5
                                # LOE rax rcx rbx rdi r8 r9 r10 r11 r12 r13 r15 edx r14d xmm0
..B1.81:                        # Preds ..B1.79 ..B1.81
                                # Execution count [1.25e+00]
        vmovss    (%r10,%r11,4), %xmm1                          #208.51
        vfmadd213ss (%r9,%r11,4), %xmm0, %xmm1                  #21.9
        vmovss    %xmm1, (%r15,%r11,4)                          #21.9
        incq      %r11                                          #19.5
        cmpq      %r12, %r11                                    #19.5
        jb        ..B1.81       # Prob 82%                      #19.5
                                # LOE rax rcx rbx rdi r8 r9 r10 r11 r12 r13 r15 edx r14d xmm0
..B1.83:                        # Preds ..B1.81 ..B1.79 ..B1.120
                                # Execution count [2.25e-01]
        vbroadcastss %xmm0, %ymm0                               #208.55
                                # LOE rax rcx rbx rdi r8 r9 r10 r12 r13 r15 edx r14d ymm0
..B1.84:                        # Preds ..B1.84 ..B1.83
                                # Execution count [1.25e+00]
        vmovups   (%r10,%r12,4), %ymm1                          #208.51
        vfmadd213ps (%r9,%r12,4), %ymm0, %ymm1                  #190.55
        vmovups   %ymm1, (%r15,%r12,4)                          #21.9
        vmovups   32(%r10,%r12,4), %ymm2                        #208.51
        vfmadd213ps 32(%r9,%r12,4), %ymm0, %ymm2                #190.55
        vmovups   %ymm2, 32(%r15,%r12,4)                        #21.9
        addq      $16, %r12                                     #19.5
        cmpq      %rcx, %r12                                    #19.5
        jb        ..B1.84       # Prob 82%                      #19.5
                                # LOE rax rcx rbx rdi r8 r9 r10 r12 r13 r15 edx r14d ymm0
..B1.86:                        # Preds ..B1.84 ..B1.118
                                # Execution count [2.25e-01]
        xorl      %r10d, %r10d                                  #19.5
        lea       1(%rcx), %r9                                  #19.5
        cmpq      %r13, %r9                                     #19.5
        ja        ..B1.90       # Prob 0%                       #19.5
                                # LOE rax rcx rbx rdi r8 r10 r13 edx r14d
..B1.87:                        # Preds ..B1.86
                                # Execution count [2.25e-01]
        addq      %rcx, %r8                                     #20.5
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        subq      %rcx, %r13                                    #19.5
        vcvtsi2ss %edx, %xmm0, %xmm0                            #208.55
        lea       (%rax,%r8,4), %r9                             #21.9
        lea       (%rdi,%r8,4), %rdx                            #190.51
        lea       (%rbx,%r8,4), %rax                            #208.51
                                # LOE rax rdx r9 r10 r13 r14d xmm0
..B1.88:                        # Preds ..B1.88 ..B1.87
                                # Execution count [1.25e+00]
        vmovss    (%rax,%r10,4), %xmm1                          #208.51
        vfmadd213ss (%rdx,%r10,4), %xmm0, %xmm1                 #21.9
        vmovss    %xmm1, (%r9,%r10,4)                           #21.9
        incq      %r10                                          #19.5
        cmpq      %r13, %r10                                    #19.5
        jb        ..B1.88       # Prob 82%                      #19.5
                                # LOE rax rdx r9 r10 r13 r14d xmm0
..B1.90:                        # Preds ..B1.88 ..B1.72 ..B1.71 ..B1.86
                                # Execution count [0.00e+00]
        movl      $.2.73_2_kmpc_loc_struct_pack.274, %edi       #19.5
        movl      %r14d, %esi                                   #19.5
        vzeroupper                                              #19.5
        call      __kmpc_for_static_fini                        #19.5
                                # LOE
..B1.91:                        # Preds ..B1.90 ..B1.68 ..B1.69
                                # Execution count [0.00e+00]
        xorl      %eax, %eax                                    #19.5
        movq      104(%rsp), %r15                               #19.5[spill]
	.cfi_restore 15
        movq      112(%rsp), %r14                               #19.5[spill]
	.cfi_restore 14
        movq      120(%rsp), %r13                               #19.5[spill]
	.cfi_restore 13
        movq      128(%rsp), %r12                               #19.5[spill]
	.cfi_restore 12
        movq      136(%rsp), %rbx                               #19.5[spill]
	.cfi_restore 3
        movq      %rbp, %rsp                                    #19.5
        popq      %rbp                                          #19.5
	.cfi_def_cfa 7, 8
	.cfi_restore 6
        ret                                                     #19.5
	.cfi_def_cfa 6, 16
	.cfi_escape 0x10, 0x03, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x88, 0xff, 0xff, 0xff, 0x22
	.cfi_offset 6, -16
	.cfi_escape 0x10, 0x0c, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0d, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x78, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0e, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x70, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0f, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0x68, 0xff, 0xff, 0xff, 0x22
                                # LOE
..B1.92:                        # Preds ..B1.28 ..B1.31 ..B1.33
                                # Execution count [2.25e-02]: Infreq
        movq      %rbx, %r8                                     #14.30
        jmp       ..B1.41       # Prob 100%                     #14.30
                                # LOE rax rdx rsi rdi r8 ecx
..B1.94:                        # Preds ..B1.29
                                # Execution count [2.25e-02]: Infreq
        movq      %rdi, %r8                                     #14.30
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        vcvtsi2ss %ecx, %xmm0, %xmm0                            #208.55
        andq      $-8, %r8                                      #14.30
        movq      %rbx, %r9                                     #14.30
        jmp       ..B1.38       # Prob 100%                     #14.30
                                # LOE rax rdx rsi rdi r8 r9 ecx xmm0
..___tag_value_main.6:
..___tag_value_main.1:
..B1.96:                        # Preds ..B1.2 ..B1.65
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #60.39
                                # LOE
..B1.97:                        # Preds ..B1.96
                                # Execution count [0.00e+00]: Infreq
        xorl      %eax, %eax                                    #60.39
        movq      (%rsp), %rdi                                  #60.39
..___tag_value_main.107:
        call      __cxa_call_unexpected                         #60.39
..___tag_value_main.108:
                                # LOE
..B1.98:                        # Preds ..B1.102 ..B1.97
                                # Execution count [0.00e+00]: Infreq
        movq      (%rsp), %rdi                                  #60.39
..___tag_value_main.109:
        call      _Unwind_Resume                                #60.39
..___tag_value_main.110:
                                # LOE
..___tag_value_main.5:
..___tag_value_main.2:
..B1.99:                        # Preds ..B1.5 ..B1.63
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #60.39
                                # LOE
..B1.100:                       # Preds ..B1.99
                                # Execution count [0.00e+00]: Infreq
        xorl      %eax, %eax                                    #60.39
        movq      (%rsp), %rdi                                  #60.39
..___tag_value_main.111:
        call      __cxa_call_unexpected                         #60.39
..___tag_value_main.112:
                                # LOE
..B1.102:                       # Preds ..B1.106 ..B1.100 ..B1.104
                                # Execution count [0.00e+00]: Infreq
        movq      64(%rsp), %rdi                                #11.22
..___tag_value_main.113:
#       Squeeze::internal::aligned_free(void *)
        call      _ZN7Squeeze8internal12aligned_freeEPv         #221.5
..___tag_value_main.114:
        jmp       ..B1.98       # Prob 100%                     #221.5
                                # LOE
..___tag_value_main.3:
..B1.104:                       # Preds ..B1.100 ..B1.109
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #11.22
        jmp       ..B1.102      # Prob 100%                     #11.22
                                # LOE
..___tag_value_main.4:
..B1.105:                       # Preds ..B1.60 ..B1.58 ..B1.19 ..B1.17 ..B1.15
                                #       ..B1.13 ..B1.11 ..B1.9
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #11.31
                                # LOE
..B1.106:                       # Preds ..B1.105
                                # Execution count [0.00e+00]: Infreq
        movq      80(%rsp), %rdi                                #11.31
..___tag_value_main.115:
#       Squeeze::internal::aligned_free(void *)
        call      _ZN7Squeeze8internal12aligned_freeEPv         #221.5
..___tag_value_main.116:
        jmp       ..B1.102      # Prob 100%                     #221.5
                                # LOE
..B1.108:                       # Preds ..B1.7
                                # Execution count [5.11e-03]: Infreq
        movl      $8, %edi                                      #194.26
        call      __cxa_allocate_exception                      #194.26
                                # LOE rax
..B1.109:                       # Preds ..B1.108
                                # Execution count [5.11e-03]: Infreq
        movq      %rax, %rdi                                    #194.26
        movl      $_ZTISt9bad_alloc, %esi                       #194.26
        movl      $_ZNSt9bad_allocD1Ev, %edx                    #194.26
        movq      $_ZTVSt9bad_alloc+16, (%rax)                  #58.5
..___tag_value_main.117:
        call      __cxa_throw                                   #194.26
..___tag_value_main.118:
                                # LOE
..B1.113:                       # Preds ..B1.4
                                # Execution count [5.11e-03]: Infreq
        movl      $8, %edi                                      #194.26
        call      __cxa_allocate_exception                      #194.26
                                # LOE rax
..B1.114:                       # Preds ..B1.113
                                # Execution count [5.11e-03]: Infreq
        movq      %rax, %rdi                                    #194.26
        movl      $_ZTISt9bad_alloc, %esi                       #194.26
        movl      $_ZNSt9bad_allocD1Ev, %edx                    #194.26
        movq      $_ZTVSt9bad_alloc+16, (%rax)                  #58.5
..___tag_value_main.119:
        call      __cxa_throw                                   #194.26
..___tag_value_main.120:
                                # LOE
..B1.118:                       # Preds ..B1.73 ..B1.76 ..B1.78
                                # Execution count [2.25e-02]: Infreq
        xorl      %ecx, %ecx                                    #19.5
        jmp       ..B1.86       # Prob 100%                     #19.5
                                # LOE rax rcx rbx rdi r8 r13 edx r14d
..B1.120:                       # Preds ..B1.74
                                # Execution count [2.25e-02]: Infreq
        movq      %r13, %rcx                                    #19.5
        vxorps    %xmm0, %xmm0, %xmm0                           #208.55
        vcvtsi2ss %edx, %xmm0, %xmm0                            #208.55
        andq      $-16, %rcx                                    #19.5
        xorl      %r12d, %r12d                                  #19.5
        lea       (%rbx,%r8,4), %r10                            #208.51
        lea       (%rdi,%r8,4), %r9                             #190.51
        jmp       ..B1.83       # Prob 100%                     #190.51
        .align    16,0x90
                                # LOE rax rcx rbx rdi r8 r9 r10 r12 r13 r15 edx r14d xmm0
	.cfi_endproc
# mark_end;
	.type	main,@function
	.size	main,.-main
..LNmain.0:
	.section .gcc_except_table, "a"
	.align 4
main$$LSDA:
	.byte	255
	.byte	0
	.uleb128	..___tag_value_main.125 - ..___tag_value_main.124
..___tag_value_main.124:
	.byte	1
	.uleb128	..___tag_value_main.123 - ..___tag_value_main.122
..___tag_value_main.122:
	.uleb128	..___tag_value_main.22 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.23 - ..___tag_value_main.22
	.byte	0
	.byte	0
	.uleb128	..___tag_value_main.24 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.25 - ..___tag_value_main.24
	.uleb128	..___tag_value_main.1 - ..___tag_value_main.7
	.byte	1
	.uleb128	..___tag_value_main.26 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.27 - ..___tag_value_main.26
	.uleb128	..___tag_value_main.2 - ..___tag_value_main.7
	.byte	1
	.uleb128	..___tag_value_main.28 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.39 - ..___tag_value_main.28
	.uleb128	..___tag_value_main.4 - ..___tag_value_main.7
	.byte	0
	.uleb128	..___tag_value_main.50 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.53 - ..___tag_value_main.50
	.uleb128	..___tag_value_main.4 - ..___tag_value_main.7
	.byte	0
	.uleb128	..___tag_value_main.54 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.55 - ..___tag_value_main.54
	.uleb128	..___tag_value_main.5 - ..___tag_value_main.7
	.byte	1
	.uleb128	..___tag_value_main.56 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.57 - ..___tag_value_main.56
	.uleb128	..___tag_value_main.6 - ..___tag_value_main.7
	.byte	1
	.uleb128	..___tag_value_main.58 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.110 - ..___tag_value_main.58
	.byte	0
	.byte	0
	.uleb128	..___tag_value_main.111 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.112 - ..___tag_value_main.111
	.uleb128	..___tag_value_main.3 - ..___tag_value_main.7
	.byte	0
	.uleb128	..___tag_value_main.117 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.118 - ..___tag_value_main.117
	.uleb128	..___tag_value_main.3 - ..___tag_value_main.7
	.byte	0
	.uleb128	..___tag_value_main.119 - ..___tag_value_main.7
	.uleb128	..___tag_value_main.120 - ..___tag_value_main.119
	.byte	0
	.byte	0
..___tag_value_main.123:
	.byte	127
	.byte	0
	.long	0x00000000,0x00000000
..___tag_value_main.125:
	.byte	0
	.data
	.align 4
	.align 4
.2.73_2_kmpc_loc_struct_pack.217:
	.long	0
	.long	838860802
	.long	0
	.long	0
	.quad	.2.73_2__kmpc_loc_pack.216
	.align 4
.2.73_2__kmpc_loc_pack.216:
	.byte	59
	.byte	117
	.byte	110
	.byte	107
	.byte	110
	.byte	111
	.byte	119
	.byte	110
	.byte	59
	.byte	109
	.byte	97
	.byte	105
	.byte	110
	.byte	59
	.byte	57
	.byte	59
	.byte	57
	.byte	59
	.byte	59
	.space 1, 0x00 	# pad
	.align 4
.2.73_2_kmpc_loc_struct_pack.228:
	.long	0
	.long	838860802
	.long	0
	.long	0
	.quad	.2.73_2__kmpc_loc_pack.227
	.align 4
.2.73_2__kmpc_loc_pack.227:
	.byte	59
	.byte	117
	.byte	110
	.byte	107
	.byte	110
	.byte	111
	.byte	119
	.byte	110
	.byte	59
	.byte	109
	.byte	97
	.byte	105
	.byte	110
	.byte	59
	.byte	49
	.byte	57
	.byte	59
	.byte	49
	.byte	57
	.byte	59
	.byte	59
	.space 3, 0x00 	# pad
	.align 4
.2.73_2_kmpc_loc_struct_pack.294:
	.long	0
	.long	838860802
	.long	0
	.long	0
	.quad	.2.73_2__kmpc_loc_pack.293
	.align 4
.2.73_2__kmpc_loc_pack.293:
	.byte	59
	.byte	117
	.byte	110
	.byte	107
	.byte	110
	.byte	111
	.byte	119
	.byte	110
	.byte	59
	.byte	109
	.byte	97
	.byte	105
	.byte	110
	.byte	59
	.byte	49
	.byte	57
	.byte	59
	.byte	50
	.byte	48
	.byte	59
	.byte	59
	.space 3, 0x00 	# pad
	.align 4
.2.73_2_kmpc_loc_struct_pack.236:
	.long	0
	.long	838860802
	.long	0
	.long	0
	.quad	.2.73_2__kmpc_loc_pack.235
	.align 4
.2.73_2__kmpc_loc_pack.235:
	.byte	59
	.byte	117
	.byte	110
	.byte	107
	.byte	110
	.byte	111
	.byte	119
	.byte	110
	.byte	59
	.byte	109
	.byte	97
	.byte	105
	.byte	110
	.byte	59
	.byte	51
	.byte	50
	.byte	59
	.byte	51
	.byte	50
	.byte	59
	.byte	59
	.space 3, 0x00 	# pad
	.align 4
.2.73_2_kmpc_loc_struct_pack.274:
	.long	0
	.long	838861314
	.long	0
	.long	0
	.quad	.2.73_2__kmpc_loc_pack.273
	.align 4
.2.73_2__kmpc_loc_pack.273:
	.byte	59
	.byte	117
	.byte	110
	.byte	107
	.byte	110
	.byte	111
	.byte	119
	.byte	110
	.byte	59
	.byte	109
	.byte	97
	.byte	105
	.byte	110
	.byte	59
	.byte	49
	.byte	57
	.byte	59
	.byte	50
	.byte	48
	.byte	59
	.byte	59
	.data
# -- End  main, L_main_19__par_region0_2.4
	.text
.L_2__routine_start__ZN7Squeeze8internal12aligned_freeEPv_1:
# -- Begin  _ZN7Squeeze8internal12aligned_freeEPv
	.text
# mark_begin;
       .align    16,0x90
	.globl _ZN7Squeeze8internal12aligned_freeEPv
# --- Squeeze::internal::aligned_free(void *)
_ZN7Squeeze8internal12aligned_freeEPv:
# parameter 1(ptr): %rdi
..B2.1:                         # Preds ..B2.0
                                # Execution count [1.00e+00]
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0xb, _ZN7Squeeze8internal12aligned_freeEPv$$LSDA
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.127:
..L128:
                                                        #60.39
        pushq     %rsi                                          #60.39
	.cfi_def_cfa_offset 16
        testq     %rdi, %rdi                                    #61.14
        je        ..B2.3        # Prob 15%                      #61.14
                                # LOE rbx rbp rdi r12 r13 r14 r15
..B2.2:                         # Preds ..B2.1
                                # Execution count [8.42e-01]
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.130:
#       MKL_free(void *)
        call      MKL_free                                      #61.23
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.131:
                                # LOE rbx rbp r12 r13 r14 r15
..B2.3:                         # Preds ..B2.2 ..B2.1
                                # Execution count [1.00e+00]
        popq      %rcx                                          #62.1
	.cfi_def_cfa_offset 8
        ret                                                     #62.1
	.cfi_def_cfa_offset 16
                                # LOE
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.126:
..B2.4:                         # Preds ..B2.2
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #60.39
                                # LOE rbx rbp r12 r13 r14 r15
..B2.5:                         # Preds ..B2.4
                                # Execution count [0.00e+00]: Infreq
        xorl      %eax, %eax                                    #60.39
        movq      (%rsp), %rdi                                  #60.39
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.134:
        call      __cxa_call_unexpected                         #60.39
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.135:
                                # LOE rbx rbp r12 r13 r14 r15
..B2.6:                         # Preds ..B2.5
                                # Execution count [0.00e+00]: Infreq
        movq      (%rsp), %rdi                                  #60.39
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.136:
        call      _Unwind_Resume                                #60.39
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.137:
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	_ZN7Squeeze8internal12aligned_freeEPv,@function
	.size	_ZN7Squeeze8internal12aligned_freeEPv,.-_ZN7Squeeze8internal12aligned_freeEPv
..LN_ZN7Squeeze8internal12aligned_freeEPv.1:
	.section .gcc_except_table, "a"
	.align 4
_ZN7Squeeze8internal12aligned_freeEPv$$LSDA:
	.byte	255
	.byte	0
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.142 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.141
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.141:
	.byte	1
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.140 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.139
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.139:
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.130 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.127
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.131 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.130
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.126 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.127
	.byte	1
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.134 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.127
	.uleb128	..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.137 - ..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.134
	.byte	0
	.byte	0
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.140:
	.byte	127
	.byte	0
	.long	0x00000000,0x00000000
..___tag_value__ZN7Squeeze8internal12aligned_freeEPv.142:
	.byte	0
	.data
# -- End  _ZN7Squeeze8internal12aligned_freeEPv
	.text
.L_2__routine_start__ZN7Squeeze8internal13aligned_allocEmm_2:
# -- Begin  _ZN7Squeeze8internal13aligned_allocEmm
	.text
# mark_begin;
       .align    16,0x90
	.globl _ZN7Squeeze8internal13aligned_allocEmm
# --- Squeeze::internal::aligned_alloc(Squeeze::StdUIdx, Squeeze::StdUIdx)
_ZN7Squeeze8internal13aligned_allocEmm:
# parameter 1(alignment): %rdi
# parameter 2(size): %rsi
..B3.1:                         # Preds ..B3.0
                                # Execution count [1.00e+00]
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0xb, _ZN7Squeeze8internal13aligned_allocEmm$$LSDA
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.144:
..L145:
                                                        #56.63
        pushq     %rsi                                          #56.63
	.cfi_def_cfa_offset 16
        movl      %edi, %eax                                    #57.10
        movq      %rsi, %rdi                                    #57.10
        movl      %eax, %esi                                    #57.10
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.147:
#       MKL_malloc(size_t, int)
        call      MKL_malloc                                    #57.10
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.148:
                                # LOE rax rbx rbp r12 r13 r14 r15
..B3.3:                         # Preds ..B3.1
                                # Execution count [1.00e+00]
        popq      %rcx                                          #57.3
	.cfi_def_cfa_offset 8
        ret                                                     #57.3
	.cfi_def_cfa_offset 16
                                # LOE
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.143:
..B3.4:                         # Preds ..B3.1
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #56.63
                                # LOE rbx rbp r12 r13 r14 r15
..B3.5:                         # Preds ..B3.4
                                # Execution count [0.00e+00]: Infreq
        xorl      %eax, %eax                                    #56.63
        movq      (%rsp), %rdi                                  #56.63
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.151:
        call      __cxa_call_unexpected                         #56.63
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.152:
                                # LOE rbx rbp r12 r13 r14 r15
..B3.6:                         # Preds ..B3.5
                                # Execution count [0.00e+00]: Infreq
        movq      (%rsp), %rdi                                  #56.63
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.153:
        call      _Unwind_Resume                                #56.63
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.154:
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	_ZN7Squeeze8internal13aligned_allocEmm,@function
	.size	_ZN7Squeeze8internal13aligned_allocEmm,.-_ZN7Squeeze8internal13aligned_allocEmm
..LN_ZN7Squeeze8internal13aligned_allocEmm.2:
	.section .gcc_except_table, "a"
	.align 4
_ZN7Squeeze8internal13aligned_allocEmm$$LSDA:
	.byte	255
	.byte	0
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.159 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.158
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.158:
	.byte	1
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.157 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.156
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.156:
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.147 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.144
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.148 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.147
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.143 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.144
	.byte	1
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.151 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.144
	.uleb128	..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.154 - ..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.151
	.byte	0
	.byte	0
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.157:
	.byte	127
	.byte	0
	.long	0x00000000,0x00000000
..___tag_value__ZN7Squeeze8internal13aligned_allocEmm.159:
	.byte	0
	.data
# -- End  _ZN7Squeeze8internal13aligned_allocEmm
	.text
.L_2__routine_start__ZN7Squeeze8internal15aligned_reallocEPvmm_3:
# -- Begin  _ZN7Squeeze8internal15aligned_reallocEPvmm
	.text
# mark_begin;
       .align    16,0x90
	.globl _ZN7Squeeze8internal15aligned_reallocEPvmm
# --- Squeeze::internal::aligned_realloc(void *, Squeeze::StdUIdx, Squeeze::StdUIdx)
_ZN7Squeeze8internal15aligned_reallocEPvmm:
# parameter 1(ptr): %rdi
# parameter 2: %rsi
# parameter 3(size): %rdx
..B4.1:                         # Preds ..B4.0
                                # Execution count [1.00e+00]
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0xb, _ZN7Squeeze8internal15aligned_reallocEPvmm$$LSDA
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.161:
..L162:
                                                        #64.66
        pushq     %rsi                                          #64.66
	.cfi_def_cfa_offset 16
        movq      %rdx, %rsi                                    #65.10
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.164:
#       MKL_realloc(void *, size_t)
        call      MKL_realloc                                   #65.10
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.165:
                                # LOE rax rbx rbp r12 r13 r14 r15
..B4.3:                         # Preds ..B4.1
                                # Execution count [1.00e+00]
        popq      %rcx                                          #65.3
	.cfi_def_cfa_offset 8
        ret                                                     #65.3
	.cfi_def_cfa_offset 16
                                # LOE
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.160:
..B4.4:                         # Preds ..B4.1
                                # Execution count [0.00e+00]: Infreq
        movq      %rax, (%rsp)                                  #64.66
                                # LOE rbx rbp r12 r13 r14 r15
..B4.5:                         # Preds ..B4.4
                                # Execution count [0.00e+00]: Infreq
        xorl      %eax, %eax                                    #64.66
        movq      (%rsp), %rdi                                  #64.66
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.168:
        call      __cxa_call_unexpected                         #64.66
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.169:
                                # LOE rbx rbp r12 r13 r14 r15
..B4.6:                         # Preds ..B4.5
                                # Execution count [0.00e+00]: Infreq
        movq      (%rsp), %rdi                                  #64.66
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.170:
        call      _Unwind_Resume                                #64.66
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.171:
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	_ZN7Squeeze8internal15aligned_reallocEPvmm,@function
	.size	_ZN7Squeeze8internal15aligned_reallocEPvmm,.-_ZN7Squeeze8internal15aligned_reallocEPvmm
..LN_ZN7Squeeze8internal15aligned_reallocEPvmm.3:
	.section .gcc_except_table, "a"
	.align 4
_ZN7Squeeze8internal15aligned_reallocEPvmm$$LSDA:
	.byte	255
	.byte	0
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.176 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.175
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.175:
	.byte	1
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.174 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.173
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.173:
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.164 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.161
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.165 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.164
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.160 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.161
	.byte	1
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.168 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.161
	.uleb128	..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.171 - ..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.168
	.byte	0
	.byte	0
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.174:
	.byte	127
	.byte	0
	.long	0x00000000,0x00000000
..___tag_value__ZN7Squeeze8internal15aligned_reallocEPvmm.176:
	.byte	0
	.data
# -- End  _ZN7Squeeze8internal15aligned_reallocEPvmm
	.text
.L_2__routine_start___sti__$E_4:
# -- Begin  __sti__$E
	.text
# mark_begin;
       .align    16,0x90
# --- __sti__$E()
__sti__$E:
..B5.1:                         # Preds ..B5.0
                                # Execution count [1.00e+00]
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
..___tag_value___sti__$E.177:
..L178:
                                                        #
        pushq     %rsi                                          #
	.cfi_def_cfa_offset 16
        movl      $_ZN17_INTERNAL0f04436bSt8__ioinitE, %edi     #74.25
..___tag_value___sti__$E.180:
#       std::ios_base::Init::Init(std::ios_base::Init *)
        call      _ZNSt8ios_base4InitC1Ev                       #74.25
..___tag_value___sti__$E.181:
                                # LOE rbx rbp r12 r13 r14 r15
..B5.2:                         # Preds ..B5.1
                                # Execution count [1.00e+00]
        movl      $_ZNSt8ios_base4InitD1Ev, %edi                #74.25
        movl      $_ZN17_INTERNAL0f04436bSt8__ioinitE, %esi     #74.25
        movl      $__dso_handle, %edx                           #74.25
        addq      $8, %rsp                                      #74.25
	.cfi_def_cfa_offset 8
#       __cxa_atexit(void (*)(void *), void *, void *)
        jmp       __cxa_atexit                                  #74.25
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	__sti__$E,@function
	.size	__sti__$E,.-__sti__$E
..LN__sti__$E.4:
	.data
# -- End  __sti__$E
	.bss
	.align 4
	.align 4
___kmpv_zeromain_0:
	.type	___kmpv_zeromain_0,@object
	.size	___kmpv_zeromain_0,4
	.space 4	# pad
	.align 1
_ZN17_INTERNAL0f04436bSt8__ioinitE:
	.type	_ZN17_INTERNAL0f04436bSt8__ioinitE,@object
	.size	_ZN17_INTERNAL0f04436bSt8__ioinitE,1
	.space 1	# pad
	.section .rodata, "a"
	.align 4
	.align 4
.L_2il0floatpacket.5:
	.long	0x44800000
	.type	.L_2il0floatpacket.5,@object
	.size	.L_2il0floatpacket.5,4
	.align 4
.L_2il0floatpacket.6:
	.long	0x40000000
	.type	.L_2il0floatpacket.6,@object
	.size	.L_2il0floatpacket.6,4
	.section .data._ZZNSt19_Sp_make_shared_tag5_S_tiEvE5__tag, "waG",@progbits,_ZZNSt19_Sp_make_shared_tag5_S_tiEvE5__tag,comdat
	.align 8
	.weak _ZZNSt19_Sp_make_shared_tag5_S_tiEvE5__tag
_ZZNSt19_Sp_make_shared_tag5_S_tiEvE5__tag:
	.type	_ZZNSt19_Sp_make_shared_tag5_S_tiEvE5__tag,@object
	.size	_ZZNSt19_Sp_make_shared_tag5_S_tiEvE5__tag,16
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section .data._ZZNSt8__detail18__to_chars_10_implIjEEvPcjT_E8__digits, "waG",@progbits,_ZZNSt8__detail18__to_chars_10_implIjEEvPcjT_E8__digits,comdat
	.align 32
	.weak _ZZNSt8__detail18__to_chars_10_implIjEEvPcjT_E8__digits
_ZZNSt8__detail18__to_chars_10_implIjEEvPcjT_E8__digits:
	.type	_ZZNSt8__detail18__to_chars_10_implIjEEvPcjT_E8__digits,@object
	.size	_ZZNSt8__detail18__to_chars_10_implIjEEvPcjT_E8__digits,201
	.long	825241648
	.long	858796592
	.long	892351536
	.long	925906480
	.long	959461424
	.long	825307185
	.long	858862129
	.long	892417073
	.long	925972017
	.long	959526961
	.long	825372722
	.long	858927666
	.long	892482610
	.long	926037554
	.long	959592498
	.long	825438259
	.long	858993203
	.long	892548147
	.long	926103091
	.long	959658035
	.long	825503796
	.long	859058740
	.long	892613684
	.long	926168628
	.long	959723572
	.long	825569333
	.long	859124277
	.long	892679221
	.long	926234165
	.long	959789109
	.long	825634870
	.long	859189814
	.long	892744758
	.long	926299702
	.long	959854646
	.long	825700407
	.long	859255351
	.long	892810295
	.long	926365239
	.long	959920183
	.long	825765944
	.long	859320888
	.long	892875832
	.long	926430776
	.long	959985720
	.long	825831481
	.long	859386425
	.long	892941369
	.long	926496313
	.long	960051257
	.byte	0
	.section .data._ZZNSt8__detail18__to_chars_10_implImEEvPcjT_E8__digits, "waG",@progbits,_ZZNSt8__detail18__to_chars_10_implImEEvPcjT_E8__digits,comdat
	.align 32
	.weak _ZZNSt8__detail18__to_chars_10_implImEEvPcjT_E8__digits
_ZZNSt8__detail18__to_chars_10_implImEEvPcjT_E8__digits:
	.type	_ZZNSt8__detail18__to_chars_10_implImEEvPcjT_E8__digits,@object
	.size	_ZZNSt8__detail18__to_chars_10_implImEEvPcjT_E8__digits,201
	.long	825241648
	.long	858796592
	.long	892351536
	.long	925906480
	.long	959461424
	.long	825307185
	.long	858862129
	.long	892417073
	.long	925972017
	.long	959526961
	.long	825372722
	.long	858927666
	.long	892482610
	.long	926037554
	.long	959592498
	.long	825438259
	.long	858993203
	.long	892548147
	.long	926103091
	.long	959658035
	.long	825503796
	.long	859058740
	.long	892613684
	.long	926168628
	.long	959723572
	.long	825569333
	.long	859124277
	.long	892679221
	.long	926234165
	.long	959789109
	.long	825634870
	.long	859189814
	.long	892744758
	.long	926299702
	.long	959854646
	.long	825700407
	.long	859255351
	.long	892810295
	.long	926365239
	.long	959920183
	.long	825765944
	.long	859320888
	.long	892875832
	.long	926430776
	.long	959985720
	.long	825831481
	.long	859386425
	.long	892941369
	.long	926496313
	.long	960051257
	.byte	0
	.section .data._ZZNSt8__detail18__to_chars_10_implIyEEvPcjT_E8__digits, "waG",@progbits,_ZZNSt8__detail18__to_chars_10_implIyEEvPcjT_E8__digits,comdat
	.align 32
	.weak _ZZNSt8__detail18__to_chars_10_implIyEEvPcjT_E8__digits
_ZZNSt8__detail18__to_chars_10_implIyEEvPcjT_E8__digits:
	.type	_ZZNSt8__detail18__to_chars_10_implIyEEvPcjT_E8__digits,@object
	.size	_ZZNSt8__detail18__to_chars_10_implIyEEvPcjT_E8__digits,201
	.long	825241648
	.long	858796592
	.long	892351536
	.long	925906480
	.long	959461424
	.long	825307185
	.long	858862129
	.long	892417073
	.long	925972017
	.long	959526961
	.long	825372722
	.long	858927666
	.long	892482610
	.long	926037554
	.long	959592498
	.long	825438259
	.long	858993203
	.long	892548147
	.long	926103091
	.long	959658035
	.long	825503796
	.long	859058740
	.long	892613684
	.long	926168628
	.long	959723572
	.long	825569333
	.long	859124277
	.long	892679221
	.long	926234165
	.long	959789109
	.long	825634870
	.long	859189814
	.long	892744758
	.long	926299702
	.long	959854646
	.long	825700407
	.long	859255351
	.long	892810295
	.long	926365239
	.long	959920183
	.long	825765944
	.long	859320888
	.long	892875832
	.long	926430776
	.long	959985720
	.long	825831481
	.long	859386425
	.long	892941369
	.long	926496313
	.long	960051257
	.byte	0
	.section .data._ZNSt14numeric_limitsIcE9is_signedE, "waG",@progbits,_ZNSt14numeric_limitsIcE9is_signedE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIcE9is_signedE
_ZNSt14numeric_limitsIcE9is_signedE:
	.type	_ZNSt14numeric_limitsIcE9is_signedE,@object
	.size	_ZNSt14numeric_limitsIcE9is_signedE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIwE9is_signedE, "waG",@progbits,_ZNSt14numeric_limitsIwE9is_signedE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIwE9is_signedE
_ZNSt14numeric_limitsIwE9is_signedE:
	.type	_ZNSt14numeric_limitsIwE9is_signedE,@object
	.size	_ZNSt14numeric_limitsIwE9is_signedE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIDsE9is_signedE, "waG",@progbits,_ZNSt14numeric_limitsIDsE9is_signedE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIDsE9is_signedE
_ZNSt14numeric_limitsIDsE9is_signedE:
	.type	_ZNSt14numeric_limitsIDsE9is_signedE,@object
	.size	_ZNSt14numeric_limitsIDsE9is_signedE,1
	.byte	0
	.section .data._ZNSt14numeric_limitsIDiE9is_signedE, "waG",@progbits,_ZNSt14numeric_limitsIDiE9is_signedE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIDiE9is_signedE
_ZNSt14numeric_limitsIDiE9is_signedE:
	.type	_ZNSt14numeric_limitsIDiE9is_signedE,@object
	.size	_ZNSt14numeric_limitsIDiE9is_signedE,1
	.byte	0
	.section .data._ZNSt14numeric_limitsIfE12has_infinityE, "waG",@progbits,_ZNSt14numeric_limitsIfE12has_infinityE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIfE12has_infinityE
_ZNSt14numeric_limitsIfE12has_infinityE:
	.type	_ZNSt14numeric_limitsIfE12has_infinityE,@object
	.size	_ZNSt14numeric_limitsIfE12has_infinityE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIfE13has_quiet_NaNE, "waG",@progbits,_ZNSt14numeric_limitsIfE13has_quiet_NaNE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIfE13has_quiet_NaNE
_ZNSt14numeric_limitsIfE13has_quiet_NaNE:
	.type	_ZNSt14numeric_limitsIfE13has_quiet_NaNE,@object
	.size	_ZNSt14numeric_limitsIfE13has_quiet_NaNE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIfE10has_denormE, "waG",@progbits,_ZNSt14numeric_limitsIfE10has_denormE,comdat
	.align 4
	.weak _ZNSt14numeric_limitsIfE10has_denormE
_ZNSt14numeric_limitsIfE10has_denormE:
	.type	_ZNSt14numeric_limitsIfE10has_denormE,@object
	.size	_ZNSt14numeric_limitsIfE10has_denormE,4
	.long	1
	.section .data._ZNSt14numeric_limitsIdE12has_infinityE, "waG",@progbits,_ZNSt14numeric_limitsIdE12has_infinityE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIdE12has_infinityE
_ZNSt14numeric_limitsIdE12has_infinityE:
	.type	_ZNSt14numeric_limitsIdE12has_infinityE,@object
	.size	_ZNSt14numeric_limitsIdE12has_infinityE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIdE13has_quiet_NaNE, "waG",@progbits,_ZNSt14numeric_limitsIdE13has_quiet_NaNE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIdE13has_quiet_NaNE
_ZNSt14numeric_limitsIdE13has_quiet_NaNE:
	.type	_ZNSt14numeric_limitsIdE13has_quiet_NaNE,@object
	.size	_ZNSt14numeric_limitsIdE13has_quiet_NaNE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIdE10has_denormE, "waG",@progbits,_ZNSt14numeric_limitsIdE10has_denormE,comdat
	.align 4
	.weak _ZNSt14numeric_limitsIdE10has_denormE
_ZNSt14numeric_limitsIdE10has_denormE:
	.type	_ZNSt14numeric_limitsIdE10has_denormE,@object
	.size	_ZNSt14numeric_limitsIdE10has_denormE,4
	.long	1
	.section .data._ZNSt14numeric_limitsIeE12has_infinityE, "waG",@progbits,_ZNSt14numeric_limitsIeE12has_infinityE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIeE12has_infinityE
_ZNSt14numeric_limitsIeE12has_infinityE:
	.type	_ZNSt14numeric_limitsIeE12has_infinityE,@object
	.size	_ZNSt14numeric_limitsIeE12has_infinityE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIeE13has_quiet_NaNE, "waG",@progbits,_ZNSt14numeric_limitsIeE13has_quiet_NaNE,comdat
	.align 1
	.weak _ZNSt14numeric_limitsIeE13has_quiet_NaNE
_ZNSt14numeric_limitsIeE13has_quiet_NaNE:
	.type	_ZNSt14numeric_limitsIeE13has_quiet_NaNE,@object
	.size	_ZNSt14numeric_limitsIeE13has_quiet_NaNE,1
	.byte	1
	.section .data._ZNSt14numeric_limitsIeE10has_denormE, "waG",@progbits,_ZNSt14numeric_limitsIeE10has_denormE,comdat
	.align 4
	.weak _ZNSt14numeric_limitsIeE10has_denormE
_ZNSt14numeric_limitsIeE10has_denormE:
	.type	_ZNSt14numeric_limitsIeE10has_denormE,@object
	.size	_ZNSt14numeric_limitsIeE10has_denormE,4
	.long	1
	.section .ctors, "wa"
	.align 8
__init_0:
	.type	__init_0,@object
	.size	__init_0,8
	.quad	__sti__$E
	.data
	.hidden __dso_handle
# mark_proc_addr_taken __sti__$E;
	.section .note.GNU-stack, ""
# End
