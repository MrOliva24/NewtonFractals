#include <stdio.h>
#include <math.h>

void avalp (double x, double y, double *px, double *py,
      int n, double u[], double v[]) {
      // z = x + yi;  p(z) = (z - w0)...(z - w_{n-1})
      // Computem z - w_0 pero separant les parts reals i imaginaries
      double re = x-u[0]; 
      double im = y-v[0];
      double re_temp, im_temp;

      for (int i = 1; i < n; i++){
            re_temp = re; //a 
            im_temp = im; //b                              // Utilitzant (a + bi)(c + di) = (ac - bd) + i(ad - bc) 
            re = re_temp * (x-u[i]) - im_temp * (y-v[i]);  // (ac - bd)
            im = re_temp * (y-v[i]) + im_temp * (x-u[i]);  // (ad + bc)
            //for itera desde 1 per agafar sempre la component seguent 
            //d'aquesta manera no s'avalua un complex sino el producte de dos
      }
      *px = re;
      *py = im;
}


void avaldp (double x, double y, double *dpx, double *dpy,
      int n, double u[], double v[]) {
      
      double real, complex, real_aux, complex_aux;
      double real_sum = 0., complex_sum= 0.;

      for(int i=0; i<n; i++){
            real = 1;
            complex = 0;
            for(int j = 0; j<n; j++){
                  if(i != j){
                        real_aux = real * (x - u[j]) - complex * (y - v[j]);
                        complex_aux = real * (y - v[j]) + complex * (x - u[j]);
                        real = real_aux;
                        complex = complex_aux;
                  }
            }
            real_sum += real;
            complex_sum += complex;
      }
      *dpx = real_sum;
      *dpy = complex_sum;
}


int cnvnwt (double x, double y, double tolcnv, int maxit,
      int n, double u[], double v[]) {

      

      for(int i=0; i<maxit; i++){
            double px, py, dpx, dpy;
            for(int j = 0; j<n; j++){
                  double dist = ((x - u[j]) * (x - u[j]) ) + ( (y - v[j]) * (y - v[j])) ;
                  if (sqrt(dist) < tolcnv) //comprovem si l'iterat esta a menys distancia que la tolerancia de convergècia
                  {
                        return j; 
                  } 
            }
            avalp(x, y, &px, &py, n, u, v);                         //Volem avaluar z - (p(z)/p'(z))
            avaldp(x, y, &dpx, &dpy, n, u, v);                      //Sabem que: p(z) / p'(z) = ac+bd/c^2+d^2 + (bc-ad/c^2+d^2)i
            double den = (dpx * dpx) + (dpy * dpy);
            x -= (px * dpx + py * dpy) / den;                       //ac+bd/c^2+d^2 | Aquesta part la restem a la part real de z        
            y -= (py * dpx - px * dpy) / den;                       //bc-ad/c^2+d^2 | Aquesta part la restem a la part imaginaria de z

      }
      return -1;
}
