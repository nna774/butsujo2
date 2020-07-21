/*** 1次元波動方程式の数値解  ***/
/*** 初期条件が u(x,0)=sin(2*pi*x/10) のときのプログラム  ***/

#include <stdio.h>
#include <math.h>

#define N 500

double uinit(double);

int main(void) {
  FILE *fp;
  double u[N+2], unew[N];
  float usingle[N], x[N];
  double alength, c, xdouble;
  double dx, dt;
  int i, itime, iwrite, mend;

/** 　周期区間の長さ，移動速度，時間ステップ数 **/
  alength = 10.0;
  c = -1.0;
  mend = 300;

/** 　空間刻み，時間刻み，記録間隔 **/
  dx = alength / N;
  dt = dx/2;
  iwrite = 10;

/** 　x座標の値，初期条件を関数 uinit で与える **/
  for(i = 0; i <= N-1; i++) {
   x[i] = (float)alength / N * i;
   xdouble = (double)x[i];
   u[i+1] = uinit(xdouble);
  }

/** 　区間の端を周期的につなぐ **/
  u[0] = u[N];
  u[N+1] = u[1];

/** 　書き出しファイル指定 **/
  fp = fopen("pde1ddif.txt", "w");

/** 　初期条件の書き出し， **/
  for(i = 1; i <= N; i++) {
    usingle[i-1] = u[i];
    fprintf(fp, "%11.4e %11.4e\n", x[i-1], usingle[i-1]);
  }

/** 　時間発展 **/
  for(itime = 1; itime <= mend; itime++) {
    for(i = 1; i <= N; i++) {
      unew[i] = u[i] - dt * c * (u[i+1]-u[i])/dx;
    }
    for(i = 1; i <= N; i++) u[i] = unew[i];
    u[0] = u[N];
    u[N+1] = u[1];

/** 　ファイルへの書き出し **/
    if (itime/iwrite*iwrite == itime) {
      for(i = 1; i <= N; i++) {
        usingle[i-1] = u[i];
        fprintf(fp, "%11.4e %11.4e\n", x[i-1], usingle[i-1]);
      }
      fprintf(fp, "\n\n");
    }
  }
}

/** 　初期条件を与える関数 **/
double uinit(double x) {
  if(4 < x && x < 6) return (x - 4) * (6 - x);
  return 0;
}
