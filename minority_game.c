//gcc -Wall -O2 -msse2 -DSFMT_MEXP=19937 minority_game.c -o minority_game
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "SFMT.h"
#include "SFMT.c"

sfmt_t sfmt;

int mg(int m, int n, int s, int t){
  int agent[201]={};
  int point[n][s][2];
  int win[n];
  int his = 3;
  int rand = 0;

  for (int i=0; i<n; i++){
    for (int l=0; l<m+1; l++){
      point[i][l][0] = 0;
      point[i][l][1] = 0;
    }
  }

  //s個の戦略テーブルを選択
  for (int i=0; i<n; i++){
    for (int l=0; l<s; l++){
      rand = get_rand();
      point[i][l][0] = rand % 256;
    }
  }

  for (int k=0; k<t; k++){
    if (k==0){
      rand = get_rand();
      his = rand % 8;
      for (int i=0; i<n; i++){
        for (int l=0; l<s; l++){
          if (l<s-1){
            if (l == 0){
              printf("(");
            }
            printf("%d,", point[i][l][0]);
          }
          else{printf("%d)\n", point[i][l][0]);}
        }
      }
    }
    else{
      for (int i=0; i<n; i++){
      }
    }
  }
  return (0);
}

int get_rand(){
  double rand;
  int rand2;
  rand = sfmt_genrand_real2(&sfmt);
  rand = rand*10000;
  rand2 = (int)rand;
  return (rand2);
}

int main(int argc, char *argv[]){
  unsigned long seed;
  if (argc != 2){
    printf(">exe_file seed_num\n\n");
  }
  else{
    seed = strtoul(argv[1], NULL, 10);
	  sfmt_init_gen_rand(&sfmt, seed);
    mg(3, 11, 5, 100);
  }
}