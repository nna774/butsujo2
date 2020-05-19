/*********************************************
  Runge-Kutta 法(4次)による惑星運動の軌道計算
　C言語 によるプログラム例
**********************************************/
#include <stdio.h>
#include <math.h>

int main(void) {
   FILE *fp;
   int i, j;
   double  dt;           /***          時間刻み幅          ***/
   double  x, y, u, v;   /***  惑星の位置と速度を表す変数  ***/
   double  r3[4], akx[4], aky[4], aku[4], akv[4], rx[4], ry[4], ru[4], rv[4];
                         /***  Runge-Kutta法での計算に必要な変数 ***/
   double  xnew, ynew, unew, vnew;

   dt = 0.2;

/***　初期条件の設定 ***/
   x = 1.0;
   y = 0.0;
   u = 0.0;
   v = 1.0;

   fp = fopen("RK4.txt","w");

/***　時間発展の開始 ***/
   for (i = 1; i <= 100; i++)   {
      r3[0]  = pow( sqrt( pow(x,2.0) + pow(y, 2.0) ), 3.0);
      akx[0] = u;
      aky[0] = v;
      aku[0] = -x/r3[0];
      akv[0] = -y/r3[0];

      rx[1] = x + akx[0] * dt/2;
      ry[1] = y + aky[0] * dt/2;
      ru[1] = u + aku[0] * dt/2;
      rv[1] = v + akv[0] * dt/2;

      r3[1]  = pow( sqrt( pow(rx[1],2.0) + pow(ry[1], 2.0) ), 3.0);
      akx[1] = ru[1];
      aky[1] = rv[1];
      aku[1] = -rx[1]/r3[1];
      akv[1] = -ry[1]/r3[1];

      rx[2] = x + akx[1] * dt/2;
      ry[2] = y + aky[1] * dt/2;
      ru[2] = u + aku[1] * dt/2;
      rv[2] = v + akv[1] * dt/2;

      r3[2]  = pow( sqrt( pow(rx[2],2.0) + pow(ry[2], 2.0) ), 3.0);
      akx[2] = ru[2];
      aky[2] = rv[2];
      aku[2] = -rx[2]/r3[2];
      akv[2] = -ry[2]/r3[2];

      rx[3] = x + akx[2]*dt;
      ry[3] = y + aky[2]*dt;
      ru[3] = u + aku[2]*dt;
      rv[3] = v + akv[2]*dt;

      r3[3]  = pow( sqrt( pow(rx[3],2.0) + pow(ry[3], 2.0) ), 3.0);
      akx[3] = ru[3];
      aky[3] = rv[3];
      aku[3] = -rx[3]/r3[3];
      akv[3] = -ry[3]/r3[3];

/***  Runge-Kutta 法によって 1 step 時間発展した値  ***/
      xnew = x + dt*(akx[0] + 2.0*akx[1] + 2.0*akx[2] + akx[3]) / 6.0;
      ynew = y + dt*(aky[0] + 2.0*aky[1] + 2.0*aky[2] + aky[3]) / 6.0;
      unew = u + dt*(aku[0] + 2.0*aku[1] + 2.0*aku[2] + aku[3]) / 6.0;
      vnew = v + dt*(akv[0] + 2.0*akv[1] + 2.0*akv[2] + akv[3]) / 6.0;

      x = xnew;
      y = ynew;
      u = unew;
      v = vnew;

/***  ファイルへの結果の書き出し  ***/
      fprintf(fp,"%f %f %f %f\n", x, y, u, v);
   }
}
