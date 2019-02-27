.intel_syntax noprefix
.global hilbert
.text

// RDI:= degree, RSI:= x-output, RDX:= y-output
hilbert:

  // Clear registers
  pxor xmm0, xmm0 // XMM0 - upper bound of number of coordinates 4^n

  xor rax, rax // RAX - counter till XMM0
  xor rcx, rcx // RCX:=RAX - global index, this is the number from 0 to 4^n, used instead of RAX
  xor r8, r8 // R8 - x value coordinate
  xor r9, r9 // R9 - y value coordinate
  xor r10, r10 // R10 - local index, this is the length of the current curve, starts at 4
  xor r11, r11 // R11 - upper bound of inner loop

  // XMM0:= 2^n * 2^n = 4^n - number of iterations
  movd mm0, edi
  pmuludq mm0, mm0

  hindex2xy_main_loop:

      // Exit condition at 4^n, comparison through between RCX, RAX registers
      movq rcx, mm0
      cmpq rax, rcx
      je to_return

      // Secure global index in RCX
      movq rcx, rax

      // Save globa index on the stack
      pushq rcx

      // Determine last 2 bits => position in the A, B, C or D domain of degree 1 Hilbert curve
      andq rcx, 3
      cmpq rcx, 0
      je first_coordinate
      cmpq rcx, 1
      je second_coordinate
      cmpq rcx, 2
      je third_coordinate
      cmpq rcx, 3
      je fourth_coordinate

      // initial coordinates
      first_coordinate:
          mov r8d, 0
          mov r9d, 0
          jmp weiter

      second_coordinate:
          mov r8d, 0
          mov r9d, 1
          jmp weiter

      third_coordinate:
          mov r8d, 1
          mov r9d, 1
          jmp weiter

      fourth_coordinate:
          mov r8d, 1
          mov r9d, 0

      weiter:
          // Shift global index by 2 Bits, because we already extracted first
          // pair of bits, which determine the domain in degree 1 Hilbert curve
          popq rcx
          shrq rcx, 2
          movq r10, 4

          hindex2xy_internal_loop:
              // Exit condition when we arrive at degree 2^n
              cmp r10d, edi
              jg end_hindex2xy_internal_loop

              // Use R11:=R10/2 as Hilbert curve length at degree (N-1)
              mov r11d, r10d
              shr r11d, 1

              // Secure global index
              pushq rcx

              // Compare last 2 Bits of global index and determine domain accordingly
              andq rcx, 3
              cmpq rcx, 0
              je left_bottom
              cmpq rcx, 1
              je left_upper
              cmpq rcx, 2
              je right_upper
              cmpq rcx, 3
              je right_bottom

              left_bottom:
                  pushq r8
                  pushq r9
                  popq r8
                  popq r9
                  jmp weiter_hindex2xy_internal_loop

              left_upper:
                  add r9d, r11d
                  jmp weiter_hindex2xy_internal_loop

              right_upper:
                  add r8d, r11d
                  add r9d, r11d
                  jmp weiter_hindex2xy_internal_loop

              right_bottom:
                  pushq r10

                  mov r10d, r9d
                  mov r9d, r11d
                  dec r9d
                  sub r9d, r8d
                  mov r8d, r11d
                  dec r8d
                  sub r8d, r10d
                  add r8d, r11d

                  popq r10

              weiter_hindex2xy_internal_loop:
                // Retrieve global index
                popq rcx

                // Multiply local index by 2 => Length of next Hilbert curve
                shlq r10, 1
                
                // Right-shift global index by 2 => determine A, B, C or D domain in next Hilbert curve
                // Just as under weiter
                shrq rcx, 2
                jmp hindex2xy_internal_loop

          end_hindex2xy_internal_loop:
              // Move the calculated coordinates in x and y
              mov [rsi], r8d
              mov [rdx], r9d

              // Increase memory locations by 4 (4 Bytes for unsigned int)
              addq rsi, 4
              addq rdx, 4

              // Next iteration
              incq rax
              jmp hindex2xy_main_loop

  to_return:
      ret
