#include <stdio.h>

int mdcCalculator(int num1, int num2) {
  int rest;

  do {
    rest = num1 % num2;
    num1 = num2;
    num2 = rest;
  } while (rest != 0);

  return num1;
}

int validateMdc(int k, int a[], int n[]) {
  int mdcAN, mdcN, i;

  for (i = 0; i < k - 1; i++) {
    // Verifica se mdc(ni,nj) = 1, para todo i != j
    mdcN = mdcCalculator(n[i], n[i + 1]);

    if (mdcN != 1) {
      printf("Ops! O TCR não pode ser aplicado, pois o mdc de n[%d] e n[%d] é "
             "mdc(%d,%d) = %d\n.",
             i + 1, i + 2, n[i], n[i + 1], mdcN);
      exit(1);
      return 0;
    }

    // Verifica se mdc(ai,ni) = 1, para todo i
    mdcAN = mdcCalculator(a[i], n[i]);

    if (mdcAN != 1) {
      printf("Ops! O TCR não pode ser aplicado, pois o mdc de a[%d] e n[%d] é "
             "mdc(%d,%d) = %d\n.",
             i + 1, i + 1, a[i], n[i], mdcAN);
      exit(1);
      return 0;
    }
  }
  return 1;
}

// Passo 1 - Calcula o resultado das equações de congruência parcias e armazena
// em c[i]
int modInv(int a, int b, int n) {
  int calc = 0;
  for (int c = 0; c < n; c++) {
    calc = (a * c) % n;
    if (calc == b) {
      return c;
    }
  }
}

// Passo 2 - Calcula o resultado dos Ni
int NiCalculate(int N, int n, int k) {
  int i, Ni;
  for (i = 0; i < k; i++) {
    Ni = N / n;
    return Ni;
  }
}

int main(void) {
  int k, i, mdc;
  printf(
      "Qual a quantidade de equações presentes no sistema de congruencias?\n");
  scanf("%d", &k);
  // Verifica valor de k
  if (k <= 1) {
    printf("Um sistema de congruências precisa ter mais de uma equação.\n");
    return 0;
  }

  // Declaração dos vetores e leitura de a,b e n das k equações de congruência.
  int a[k], b[k], n[k], N = 1, c[k], Ni[k], NiInv[k], res = 0;

  for (i = 0; i < k; i++) {
    printf("Insira o valor de a[%d]:\n", i + 1);
    scanf("%d", &a[i]);
    // Verifica se a != 0;
    if (a[i] == 0) {
      printf("Ops! O sistema não possui solução, pois a[%d] = 0\n", i + 1);
      return 0;
    }

    printf("Insira o valor de b[%d]:\n", i + 1);
    scanf("%d", &b[i]);

    printf("Insira o valor de n[%d]:\n", i + 1);
    scanf("%d", &n[i]);
    // Verifica se n >= 2
    if (n[i] < 2) {
      printf("Ops! O sistema não possui solução, pois n[%d] é menor que 2\n",
             i + 1);
      return 0;
    }
  }

  validateMdc(k, a, n);

  // Calcula e printa o valor de N e c
  for (i = 0; i < k; i++) {
    N *= n[i];
    c[i] = modInv(a[i], b[i], n[i]);
    printf("C[%d] = %d\n", i + 1, c[i]);
  }
  printf("N = %d\n", N);

  // Calcula e printa o valor de Ni
  for (i = 0; i < k; i++) {
    Ni[i] = NiCalculate(N, n[i], k);
    printf("N[%d] = %d\n", i + 1, Ni[i]);
  }

  // Passo 3 - Calcula e printa o valor de NiInv (Ntil)
  for (i = 0; i < k; i++) {
    NiInv[i] = modInv(Ni[i], 1, n[i]);
    printf("N_inv[%d] = %d\n", i + 1, NiInv[i]);
  }

  // Calculo Final
  for (i = 0; i < k; i++) {
    res += c[i] * Ni[i] * NiInv[i];
  }

  printf("Assim, a solução é igual a x = %d (mod %d)", res, N);

  return 0;
}