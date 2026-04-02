#pragma once

// поиск числа Фибоначчи
namespace Fib {
    int getFibMemoizationUnwrapped(int n, int* dict) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        // printf("!");

        int fir;
        if (dict[n - 2] != 0) {
            fir = dict[n - 2];
        } else {
            fir = getFibMemoizationUnwrapped(n - 2, dict);
            dict[n - 2] = fir;
        }

        int sec;
        if (dict[n - 1] != 0) {
            sec = dict[n - 1];
        } else {
            sec = getFibMemoizationUnwrapped(n - 1, dict);
            dict[n - 1] = sec;
        }
        return fir + sec;
    }

    int getFibMemoization(int n) {
        int* dict = (int*)malloc((n + 1) * sizeof(int));
        int res = getFibMemoizationUnwrapped(n, dict);
        free(dict);
        return res;
    }

    int getFibSimple(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        // printf("*");
        return getFibSimple(n - 2) + getFibSimple(n - 1);
    }

    typedef struct {
        int segment;
        int a;
        int b;
        int n;
    } Frame;

    // int getFibEmulationSimple(int n) {
    //     Stack* s = createStack(n + 1, sizeof(Frame));
    //
    //     Frame f;
    //     f.a = -1;
    //     f.b = -1;
    //     f.n = n;
    //     f.segment = 0;
    //     // printf("+ %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //     pushStack(s, &f);
    //
    //     while (s->count > 0) {
    //         peekStack(s, &f);
    //         // printf("  %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //         switch (f.segment) {
    //             case 0:
    //                 if (f.n == 0) {
    //                     // попнуть, изменить в последнем перед ним a на 0
    //                     // пушнуть обратно и изменить сегмент
    //                     popStack(s, &f);
    //                     // printf("- %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     popStack(s, &f);
    //                     // printf("- %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     f.segment++;
    //                     f.a = 0;
    //                     // printf("+ %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     pushStack(s, &f);
    //                     break;
    //                 }
    //                 if (f.n == 1) {
    //                     popStack(s, &f);
    //                     // printf("- %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     popStack(s, &f);
    //                     // printf("- %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     f.segment++;
    //                     f.b = 1;
    //                     pushStack(s, &f);
    //                     // printf("+ %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     break;
    //                 }
    //                 Frame tmp;
    //                 tmp.a = -1;
    //                 tmp.b = -1;
    //                 tmp.segment = 0;
    //                 tmp.n = f.n - 2;
    //                 pushStack(s, &tmp);
    //                 // printf("+ %d %d %d %d\n", tmp.segment, tmp.a, tmp.b, tmp.n);
    //                 break;
    //             case 1:
    //                 Frame tmp1;
    //                 tmp1.a = -1;
    //                 tmp1.b = -1;
    //                 tmp1.segment = 0;
    //                 tmp1.n = f.n - 1;
    //                 pushStack(s, &tmp1);
    //                 // printf("+ %d %d %d %d\n", tmp1.segment, tmp1.a, tmp1.b, tmp1.n);
    //                 break;
    //             case 2:
    //                 Frame tmp2;
    //                 popStack(s, &tmp2);
    //                 // printf("- %d %d %d %d\n", tmp2.segment, tmp2.a, tmp2.b, tmp2.n);
    //                 if (!popStack(s, &f)) {
    //                     // printf("! %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                     return tmp2.a + tmp2.b;
    //                 }
    //                 // printf("- %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                 f.segment++;
    //                 if (f.b != -1) {
    //                     f.a = tmp2.a + tmp2.b;
    //                 } else f.b = tmp2.a + tmp2.b;
    //                 pushStack(s, &f);
    //                 // printf("+ %d %d %d %d\n", f.segment, f.a, f.b, f.n);
    //                 break;
    //         }
    //     }
    // }

    int getFibEmulationSimple(int n) {
        Stack* s = createStack(n + 1, sizeof(Frame));

        Frame f;
        f.segment = 0;
        f.n = n;
        pushStack(s, &f);

        int res = 0;
        while (s->count > 0) {
            peekStack(s, &f);
            switch (f.segment) {
                case 0:
                    if (f.n == 0) {
                        res = 0; popStack(s, &f); break;
                    } if (f.n == 1) {
                        res = 1; popStack(s, &f); break;
                    }
                    {
                        int seg = 1;
                        editTopStack(s, 0, sizeof(int), &seg);

                        Frame tmp;
                        tmp.n = f.n - 2;
                        tmp.segment = 0;
                        pushStack(s, &tmp);
                    }
                    break;
                case 1:
                    {
                        // res -> f.a
                        editTopStack(s, sizeof(int), sizeof(int), &res);

                        // 2 -> f.segment
                        int seg = 2;
                        editTopStack(s, 0, sizeof(int), &seg);

                        Frame tmp;
                        tmp.n = f.n - 1;
                        tmp.segment = 0;
                        pushStack(s, &tmp);
                    }
                    break;
                case 2:
                    // res -> f.b
                    editTopStack(s, sizeof(int) * 2, sizeof(int), &res);

                    res = f.a + res;
                    popStack(s, &f);
                    break;
            }
        }
        return res;
    }
}