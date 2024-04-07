#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "nwtfr.h"

int main (int argc, char *argv[]) {
   double xmn, xmx, ymn, ymx, tolcnv;
   int nx, ny, maxit, narr;

   if (argc<10
         || sscanf(argv[1], "%d", &narr)!=1
         || sscanf(argv[2], "%lf", &xmn)!=1
         || sscanf(argv[3], "%lf", &xmx)!=1
         || sscanf(argv[4], "%d", &nx)!=1
         || sscanf(argv[5], "%lf", &ymn)!=1
         || sscanf(argv[6], "%lf", &ymx)!=1
         || sscanf(argv[7], "%d", &ny)!=1
         || sscanf(argv[8], "%lf", &tolcnv)!=1
         || sscanf(argv[9], "%d", &maxit)!=1
      ) {
      fprintf(stderr,"%s narr xmn xmx nx ymn ymx ny tolcnv maxit\n", argv[0]);
      return -1;
   }


      double u[narr], v[narr], x, y, r[narr], g[narr], b[narr];
      int i, j, color;

      for (i = 0; i < narr; i++) {
                scanf("%lf %lf %lf %lf %lf", &u[i], &v[i], &r[i], &g[i], &b[i]);
      }

      double dx = (xmx - xmn) / nx;
      double dy = (ymx - ymn) / ny;

      for (i = 0; i <= nx; i++) {
            x = xmn + i * dx;
            for (j = 0; j <= ny; j++) {
                  y = ymn + j * dy;
                  color = cnvnwt(x, y, tolcnv, maxit, narr, u, v);
                  if(color == -1) {
                              printf("%lf %lf %d %d %d\n", x, y, 0,0,0);
                  } else {
                              printf("%lf %lf %.0f %.0f %.0f\n", x, y, 255*r[color], 255*g[color], 255*b[color]);
                  }
            }
      }
      return 0;
}
