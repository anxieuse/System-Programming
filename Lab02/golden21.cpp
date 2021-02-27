// golden21.cpp

#include "mlisp.h"

extern double a;
extern double b;
extern double total__iterations;
extern double mphi;
extern double tolerance;
extern double xmin;

double fun(double x);
double golden__section__search(double a, double b);
double golden__start(double a, double b);
double __klv__try(double a, double b, double xa, double ya, double xb, double yb);
bool close__enough_Q(double x, double y);

double a = 7.;
double b = 9.;
double total__iterations = 0;
double mphi = (3. - sqrt(5.)) * (1. / 2.);
double tolerance = 0.001;
double xmin = 0;

/* 
(define (fun x)

 (set! x (- x (/ 15 16)))
 (+ (- x) (sin x) (expt(- x 7)4) (/ 3 10))
)
*/

double fun(double x) {
    x = x - 15. / 16.;
    return -x + sin(x) + expt(x - 7., 4.) + 0.3;
}

/* 
(define (golden-section-search a b)
 (let(
      (xmin(if(< a b)(golden-start a b)(golden-start b a )))
     )
     (newline)
     xmin
 )
)
*/

double golden__section__search(double a, double b) {
    {
        double xmin(
            a < b ? golden__start(a, b) : golden__start(b, a));
        newline();
        return xmin;
    }
}

/* 
(define (golden-start a b)
 (set! total-iterations 0)
 (let(
      (xa (+ a (* mphi(- b a))))
      (xb (+ b (-(* mphi(- b a)))))
     )
     (try a b xa (fun xa) xb (fun xb))
 )
)
*/

double golden__start(double a, double b) {
    total__iterations = 0;
    {
        double xa(
            a + mphi * (b - a));
        double xb(
            b + (-mphi * (b - a)));
        return __klv__try(a, b, xa, fun(xa), xb, fun(xb));
    }
}

/* 
(define (try a b xa ya xb yb)
 (if(close-enough? a b)
      (* (+ a b)0.5)
      (let() (display "+")
             (set! total-iterations (+ total-iterations 1))
             (cond((< ya yb)(set! b xb)
                         (set! xb xa)
                         (set! yb ya)
                         (set! xa (+ a (* mphi(- b a))))
                         (try a b xa (fun xa) xb yb)
                  )
                  (else    (set! a xa)
                         (set! xa xb)
                         (set! ya yb)
                         (set! xb (- b (* mphi(- b a))))
                         (try a b xa ya xb (fun xb))
                   )
             );cond...
      );let...
 );if...
)
 */

double __klv__try(double a, double b, double xa, double ya, double xb, double yb) {
    return (
        close__enough_Q(a, b) ? 
            ((a + b) * 0.5) :
            (display("+"), total__iterations++, (ya < yb ? 
                                                    (b = xb, xb = xa, yb = ya, xa = a + mphi * (b - a), __klv__try(a, b, xa, fun(xa), xb, yb)) : 
                                                    (a = xa, xa = xb, ya = yb, xb = b - mphi * (b - a), __klv__try(a, b, xa, ya, xb, fun(xb)))))
        );
}

/* 
(define (close-enough? x y)
  (<(abs (- x y))tolerance))
*/

bool close__enough_Q(double x, double y) {
    return abs(x - y) < tolerance;
}

int main() {
    xmin = golden__section__search(a, b);
    display("Interval=\t[");
    display(a);
    display(" , ");
    display(b);
    display("]\n");
    display("Total number of iterations=");
    display(total__iterations);
    newline();
    display("xmin=\t\t");
    display(xmin);
    newline();
    display("f(xmin)=\t");
    display(fun(xmin));
    newline();
}