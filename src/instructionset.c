#include "instructionset.h"

/*
 * Executes a single instruction at the current program counter.
 * Increases the program counter and cycle count registers somewhat.
 * Uses a large switch statement as this is turned into a jump table
 * by the compiler, (i.e. very efficient).
 */
void exec(void) {
    switch(RAM[GetPC(1)]) {
        case OP_NOP:
            AddR(4);
            break;

        case OP_LD_BC_NN:
            SetBC(GetRAMword(GetPC(2)));
            AddR(10);
            break;

        case OP_LD_BCa_NN:
            SetRAMword(BC2word(), GetRAMword(GetPC(2)));
            AddR(7);
            break;

        case OP_LD_B_N:
            RG_B = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_A_BCa:
            RG_A = GetRAMbyte(BC2word());
            AddR(7);
            break;

        case OP_LD_C_N:
            RG_C = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_DE_NN:
            SetDE(GetRAMword(GetPC(2)));
            AddR(10);
            break;

        case OP_LD_DEa_A:
            SetRAMword(DE2word(), RG_A);
            AddR(7);
            break;

        case OP_LD_D_N:
            RG_D = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_E_N:
            RG_E = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_HL_NN:
            SetHL(GetRAMword(GetPC(2)));
            AddR(10);
            break;

        case OP_LD_NNa_HL:
            SetRAMword(GetRAMword(GetPC(2)), HL2word());
            AddR(16);
            break;

        case OP_LD_H_N:
            RG_H = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_HL_NNa:
            SetHL(GetRAMword(GetRAMword(GetPC(2))));
            AddR(16);
            break;

        case OP_LD_L_N:
            RG_L = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_SP_NN:
            RG_SP = GetRAMword(GetPC(2));
            AddR(10);
            break;

        case OP_LD_NNa_A:
            SetRAMbyte(GetRAMword(GetPC(2)), RG_A);
            AddR(13);
            break;

        case OP_LD_HLa_N:
            SetRAMbyte(HL2word(), GetRAMbyte(GetPC(1)));
            AddR(10);
            break;

        case OP_LD_A_NNa:
            RG_A = GetRAMbyte(GetRAMword(GetPC(2)));
            AddR(13);
            break;

        case OP_LD_A_N:
            RG_A = GetRAMbyte(GetPC(1));
            AddR(7);
            break;

        case OP_LD_B_B:
            AddR(4);
            break;

        case OP_LD_B_C:
            RG_B = RG_C;
            AddR(4);
            break;

        case OP_LD_B_D:
            RG_B = RG_D;
            AddR(4);
            break;

        case OP_LD_B_E:
            RG_B = RG_E;
            AddR(4);
            break;

        case OP_LD_B_H:
            RG_B = RG_H;
            AddR(4);
            break;

        case OP_LD_B_L:
            RG_B = RG_L;
            AddR(4);
            break;

        case OP_LD_B_HLa:
            RG_B = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_B_A:
            RG_B = RG_A;
            AddR(4);
            break;

        case OP_LD_C_B:
            RG_C = RG_B;
            AddR(4);
            break;

        case OP_LD_C_C:
            AddR(4);
            break;

        case OP_LD_C_D:
            RG_C = RG_D;
            AddR(4);
            break;

        case OP_LD_C_E:
            RG_C = RG_E;
            AddR(4);
            break;

        case OP_LD_C_H:
            RG_C = RG_H;
            AddR(4);
            break;

        case OP_LD_C_L:
            RG_C = RG_L;
            AddR(4);
            break;

        case OP_LD_C_HLa:
            RG_C = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_C_A:
            RG_C = RG_A;
            AddR(4);
            break;

        case OP_LD_D_B:
            RG_D = RG_B;
            AddR(4);
            break;

        case OP_LD_D_C:
            RG_D = RG_C;
            AddR(4);
            break;

        case OP_LD_D_D:
            AddR(4);
            break;

        case OP_LD_D_E:
            RG_D = RG_E;
            AddR(4);
            break;

        case OP_LD_D_H:
            RG_D = RG_H;
            AddR(4);
            break;

        case OP_LD_D_L:
            RG_D = RG_L;
            AddR(4);
            break;

        case OP_LD_D_HLa:
            RG_D = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_D_A:
            RG_D = RG_A;
            AddR(4);
            break;

        case OP_LD_E_B:
            RG_E = RG_B;
            AddR(4);
            break;

        case OP_LD_E_C:
            RG_E = RG_C;
            AddR(4);
            break;

        case OP_LD_E_D:
            RG_E = RG_D;
            AddR(4);
            break;

        case OP_LD_E_E:
            AddR(4);
            break;

        case OP_LD_E_H:
            RG_E = RG_H;
            AddR(4);
            break;

        case OP_LD_E_L:
            RG_E = RG_L;
            AddR(4);
            break;

        case OP_LD_E_HLa:
            RG_E = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_E_A:
            RG_E = RG_A;
            AddR(4);
            break;

        case OP_LD_H_B:
            RG_H = RG_B;
            AddR(4);
            break;

        case OP_LD_H_C:
            RG_H = RG_C;
            AddR(4);
            break;

        case OP_LD_H_D:
            RG_H = RG_D;
            AddR(4);
            break;

        case OP_LD_H_E:
            RG_H = RG_E;
            AddR(4);
            break;

        case OP_LD_H_H:
            AddR(4);
            break;

        case OP_LD_H_L:
            RG_H = RG_L;
            AddR(4);
            break;

        case OP_LD_H_HLa:
            RG_H = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_H_A:
            RG_H = RG_A;
            AddR(4);
            break;

        case OP_LD_L_B:
            RG_L = RG_B;
            AddR(4);
            break;

        case OP_LD_L_C:
            RG_L = RG_C;
            AddR(4);
            break;

        case OP_LD_L_D:
            RG_L = RG_D;
            AddR(4);
            break;

        case OP_LD_L_E:
            RG_L = RG_E;
            AddR(4);
            break;

        case OP_LD_L_H:
            RG_L = RG_H;
            AddR(4);
            break;

        case OP_LD_L_L:
            AddR(4);
            break;

        case OP_LD_L_HLa:
            RG_L = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_L_A:
            RG_L = RG_A;
            AddR(4);
            break;

        case OP_LD_HLa_B:
            SetRAMbyte(HL2word(), RG_B);
            AddR(4);
            break;

        case OP_LD_HLa_C:
            SetRAMbyte(HL2word(), RG_C);
            AddR(4);
            break;

        case OP_LD_HLa_D:
            SetRAMbyte(HL2word(), RG_D);
            AddR(4);
            break;

        case OP_LD_HLa_E:
            SetRAMbyte(HL2word(), RG_E);
            AddR(4);
            break;

        case OP_LD_HLa_H:
            SetRAMbyte(HL2word(), RG_H);
            AddR(4);
            break;

        case OP_LD_HLa_L:
            SetRAMbyte(HL2word(), RG_L);
            AddR(4);
            break;

        case OP_LD_HLa_A:
            SetRAMbyte(HL2word(), RG_A);
            AddR(4);
            break;

        case OP_HALT:
            /* TODO: implement halt simulation */
            break;

        case OP_LD_A_B:
            RG_A = RG_B;
            AddR(4);
            break;

        case OP_LD_A_C:
            RG_A = RG_C;
            AddR(4);
            break;

        case OP_LD_A_D:
            RG_A = RG_D;
            AddR(4);
            break;

        case OP_LD_A_E:
            RG_A = RG_E;
            AddR(4);
            break;

        case OP_LD_A_H:
            RG_A = RG_H;
            AddR(4);
            break;

        case OP_LD_A_L:
            RG_A = RG_L;
            AddR(4);
            break;

        case OP_LD_A_HLa:
            RG_A = GetRAMbyte(HL2word());
            AddR(7);
            break;

        case OP_LD_A_A:
            AddR(4);
            break;
    }
}
