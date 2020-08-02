/** 演習課題11　拡散方程式の陰解法， **/
/**   C言語  サンプルプログラム      **/

#include <stdio.h>
#include <math.h>

#define N 100

/** 初期条件と解析解を与える定義文   **/
#define  UINIT(xp) ( (1/sqrt(4*pi*sigma*t0))     * exp(-pow((xp)-5.0,2.0)/(4*sigma*t0))     )
#define  USOL(xp)  ( (1/sqrt(4*pi*sigma*(t+t0))) * exp(-pow((xp)-5.0,2.0)/(4*sigma*(t+t0))) )

int main(void) {
     FILE *fp;
     double a[N-1], b[N-1], c[N-1], d[N-1];
     double u[N+1], unew[N+1], x[N+1];
     double pi, alength, sigma, AL, theta;
     double tstart, tend, t0, trec, dtrec;
     double t, dx, dt;
     double alpha, bumbo;
     int i, istep, iend;
     float r1, r2, r3, r4;

/**  定数(円周率）   **/
    pi = atan(1.0)*4;

/***** パラメータ設定 *****/
 /** 区間の長さ **/
    alength = 10.0;

 /** 空間刻み数 N は parameter 文で指定 **/

 /** 拡散係数 **/
    sigma = 0.1;

 /** L=2*sigma*Δt/(Δx)^2 **/
    AL = 20.0;

 /** 陰解法の割合（θ=0：陽解法，1：完全陰解法） **/
    theta = 1.0;

 /** 初期時刻と最終時刻 **/
    tstart = 0.0;
    tend = 5.0;

 /** 初期条件の時刻パラメータ **/
    t0 = 1.0;

 /** データ記録の時間間隔 **/
    dtrec = 1.0;

 /** データ記録ファイル **/
    fp = fopen("implicit.txt","w");

/*****  以上パラメータ設定  *****/

/** 刻み幅，ステップ数 **/
    dx = alength / N;
    dt = pow(dx,2.0) * AL / (2*sigma);
    iend = (tend-tstart)/dt + 1;

/** 初期条件設定 **/
    x[0] = 0;
    u[0] = 0;

    for(i = 1; i <= N-1; i++) {
        x[i] = alength/N*i;
        u[i] = UINIT(x[i]);
    }

    x[N] = alength;
    u[N] = 0.0;

    t = tstart;
    trec = tstart+dtrec;

/** 初期条件の記録 **/
    for(i = 0; i <= N; i++) {
        r1 = x[i];
        r2 = u[i];
        r3 = UINIT(x[i]);
        r4 = t;
        fprintf(fp, "%12.5e %12.5e %12.5e %12.5e\n", r1, r2, r3, r4);
    }

/** 係数行列作成 **/
    alpha = AL * theta / 2;

    for(istep = 0; istep <= iend; istep++) {
       for(i = 1; i <= N-1; i++) {
           a[i-1] = -alpha;
           b[i-1] = 1 + 2*alpha;
           c[i-1] = -alpha;
           d[i-1] = u[i] + AL*(1-theta)/2*(u[i+1]-2*u[i]+u[i-1]);
       }

/** 一次方程式をThomas アルゴリズムで解く **/

       c[0] = c[0] / b[0];
       d[0] = d[0] / b[0];

       for(i = 1; i <= N-2; i++) {
           bumbo = b[i] - a[i] * c[i-1];
           c[i]  = c[i]/bumbo;
           d[i]  = (d[i]-a[i]*d[i-1])/bumbo;
       }

       unew[0] = 0.0;
       unew[N] = 0.0;
       unew[N-1] = d[N-2];
       for(i = N-2; i >= 1; i--) {
           unew[i] = d[i-1] - c[i-1] * unew[i+1];
       }

       for(i = 0; i <= N; i++) {
           u[i] = unew[i];
       }

/** 時間を進める **/
       t = t + dt;

/** 記録時刻であれば記録する **/
       if(trec-dt/2 <= t && t < trec+dt/2) {
          for(i = 0; i <= N; i++) {
/** x座標  **/
              r1 = x[i];
/** 数値解 **/
              r2 = u[i];
/** 解析解 **/
              r3 = USOL(x[i]);
/** 時刻   **/
              r4 = t;
              fprintf(fp, "%12.5e %12.5e %12.5e %12.5e\n", r1, r2, r3, r4);
          }

/** 次の記録時刻の設定 **/
          trec = trec + dtrec;
       }


/** 最終時刻であれば止める **/
       if(fabs(t-tend) < dt/2) {
            break;
       }

   }

   fclose(fp);
}
