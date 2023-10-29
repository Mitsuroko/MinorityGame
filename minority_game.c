//gcc -Wall -O2 -msse2 -DSFMT_MEXP=19937 minority_game.c -o minority_game
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "SFMT.h"
#include "SFMT.c"

sfmt_t sfmt;

int mg(int m, int n, int s, int t){
  int agent[n];
  int win;
  unsigned int ac = 1;
  int his = 3;
  unsigned int rand = 0;
  int action[n];
  int table_num[n];
  int much[2] = {0, 0};
  int temp_point[s];

  for (int a=0; a<m; a++){ac = ac*2;}
  short int point[n][s][ac+1];
  int temp_table[ac];

  //初期化
  for (int i=0; i<n; i++){
    for (int l=0; l<s; l++){
      for (int j=0; j<ac+1; j++){
        point[i][l][j] = 0;
      }
    }
  }

  //s個の戦略テーブルを選択
  printf("ac=%d\n", ac);
  for (int i=0; i<n; i++){
    for (int l=0; l<s; l++){
      for (int j=0; j<ac; j++){
        rand = get_rand();
        rand = rand % 2;
        if (rand == 1){
          point[i][l][j] = 1;
        }
        else{point[i][l][j] = 0;}
      }
      point[i][l][ac] = 0;
    }
  }
  for (int k=0; k<t; k++){
    much[0] = 0;
    much[1] = 0;
    win = 0;
    if (k==0){
      //1ステップ目の履歴をランダムで作成
      rand = get_rand();
      his = rand % ac;
    }
    printf("his=%d\n", his);
    for (int i=0; i<n; i++){
      //もっとも高いポイントのテーブルを選ぶ
      for (int l=0; l<s; l++){
        temp_point[l] = point[i][l][ac];
      }
      printf("agent%d [table_point=", i);
      table_num[i] = select_table(temp_point, s);
      for (int l=0; l<ac; l++){
        temp_table[l] = point[i][table_num[i]][l];
      }
      action[i] = point[i][table_num[i]][his];
      printf("selected_table=%d, action=%d]\n", table_num[i], action[i]);
      if (action[i] == 0){
        much[0]+=1;
      }
      else{much[1]+=1;}
    }
    if (much[0] < much[1]){
        win = 0;
    }
    else{win = 1;}
    printf("result [team0=%d team1=%d win=%d]\n\n", much[0], much[1], win);
    for (int i=0; i<n; i++){
      if (win == action[i]){
        point[i][table_num[i]][ac] += 1;
      }
      else{point[i][table_num[i]][ac] -= 1;}
    }
    his = renew_hist(his, win, ac);
  }
  return (0);
}

int get_rand(){
  double rand;
  unsigned int rand2;
  rand = sfmt_genrand_real2(&sfmt);
  rand = rand*130000;
  rand2 = (int)rand;
  return (rand2);
}

int renew_hist(int his, int win, int ac){
  his <<= 1;
  if (his >= ac){
    his -= ac;
  }
  his += win;
  return (his);
}

int make_decision(int his, int *table, int ac){
  int decision = 0;
  for (int i=0; i++; i<his){
    decision = table[i];
  }
  return (decision);
}

int select_table(int *point, int s){
  int temp = 0;
  int rand = 0;
  int num = 0;
  int stack = 0;
  int table_num[64];
  for (int i=0; i<s; i++){
    printf("%d", point[i]);
    if (i == 0){
      temp = point[i];
      stack += 1;
      table_num[stack-1] = i;
    }
    else{
      if (temp < point[i]){
        temp = point[i];
        stack = 1;
        for (int l=0; l<64; l++){
          table_num[l] = 0;
        }
        table_num[stack-1] = i;
      }
      else if (temp == point[i]){
        stack += 1;
        table_num[stack-1] = i;
      }
    }
  }
  rand = get_rand();
  num = rand % stack;
  printf(", ");
  return (table_num[num]);
}

void show_int(int x){
  int i;
  printf("%4u  %02x  ", x, x);
  for (i = 15; i >= 0; i--){
    printf("%d", (x>>i) & 1);
  }
  printf("\n");
}

int main(int argc, char *argv[]){
  unsigned long seed;
  if (argc != 2){
    printf(">exe_file seed_num\n\n");
  }
  else{
    seed = strtoul(argv[1], NULL, 10);
	  sfmt_init_gen_rand(&sfmt, seed);
    mg(11, 201, 2, 5);
  }
}