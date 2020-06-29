/***  演習課題５：サンプルプログラム                                             ***/
/***  特殊相対論的な場合のRutherford 散乱                                        ***/
/***  ここでは 1次の symplectic 法を用いる．                                     ***/
/***  注意：このような計算では，時間刻み幅をより小さくしても結果が同じであるこ   ***/
/***  とを確認すること．どの程度時間刻みを小さくとれば十分かということは，       ***/
/***  あらかじめには分からないのが普通である．                                   ***/

#include <stdio.h>
#include <math.h>

int main(void)
{
   FILE *fp;
   int i, j, n, ngraph;
   double dt;

   double x, y, vx, vy, px, py;
   double xnew, ynew, pxnew, pynew, rnew;
   double v2, p2, c, c2;

/*** ステップ数 ***/
   n = 5000;

/*** ファイルの指定 ***/
   fp = fopen("rela.txt", "w");
      
/*** 時間刻み，プロットする点の間隔 ***/
   dt = 3.0 / n;
   ngraph = 5;

/*** 光速と光速の二乗 ***/
   c = 12.0;
   c2 = c * c;

/*** 20種類の初期値のループ ***/
   for(j = 0; j <= 19; j++)
   {

/*** 初期条件 ***/
      x = -10;
      y = 0.1-0.2*j/19;
      vx = 10;
      vy = 0;

/*** 速度の二乗と運動量 ***/
      v2 = pow(vx,2) + pow(vy,2);
      px = vx/sqrt(1-v2/c2);
      py = vy/sqrt(1-v2/c2);

/*** 時間発展 ***/
      for(i = 1; i <= n; i++)
      {
         p2 = pow(px, 2) + pow(py, 2);
         xnew = x+px*dt/sqrt(p2/c2+1);
         ynew = y+py*dt/sqrt(p2/c2+1);
         rnew = sqrt(pow(xnew,2)+pow(ynew,2));
         pxnew = px+xnew/pow(rnew,3)*dt;
         pynew = py+ynew/pow(rnew,3)*dt;

         x = xnew;
         y = ynew;
         px = pxnew;
         py = pynew;

/*** ファイルへの記録 ***/
         if(i/ngraph*ngraph == i)
         {
            fprintf(fp, "%12.5e %12.5e %12.5e %12.5e\n", x, y, px, py);
         }
      }
   }

}
