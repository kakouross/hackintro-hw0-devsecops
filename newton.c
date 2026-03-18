#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 double f(double a_0, double a_1, double a_2, double a_3, double a_4, double a_5, double x) {                                   /*Δήλωση της συνάρτησης f, που περιέχει το πολυόνυμο 5ου βαθμού*/
    return (a_0 + a_1*x + a_2*x*x + a_3*x*x*x + a_4*x*x*x*x + a_5*x*x*x*x*x);
 }

 double f1(double a_0, double a_1, double a_2, double a_3, double a_4, double a_5, double x) {                                  /*Δήλωση της συνάρτησης f1, που περιέχει την παράγωγο της συνάρτησης f*/
    return (0*a_0 + a_1*1 + a_2*2*x + a_3*3*x*x + a_4*4*x*x*x + a_5*5*x*x*x*x);
 }

 double x2;                                                                                                                  
 int rootfound=0;
 int i=1;

int main(int argc, char **argv) {
    
    if(argc != 8) {
        printf("7 numbers required\n");
        return 1;
    }
    
    double a_0 = atof(argv[1]);
    double a_1 = atof(argv[2]);
    double a_2 = atof(argv[3]);
    double a_3 = atof(argv[4]);
    double a_4 = atof(argv[5]);
    double a_5 = atof(argv[6]);
    double x = atof(argv[7]);
    
                                                                                                                       
    while(rootfound==0) {                                                                                                       /*Ο αλγόριθμος θα επαναλαμβάνεται μέχρι η μεταβλητή rootfound να λάβει την τιμή 1, μέχρι δηλαδή να βρεθεί ρίζα*/
        x2 = x - f(a_0, a_1, a_2, a_3, a_4, a_5, x)/f1(a_0, a_1, a_2, a_3, a_4, a_5, x);                                        /*Στη μεταβλητή x2 εκχωρείται η τιμή της νέας ρίζας σύμφωνα με τη μέθοδο newton*/      
        
        if(fabs(x2-x) < 1.0e-6) {                                                                                               /*1η συνθήκη τερματισμού. Αν ισχύει τότε βρέθηκε ρίζα*/
            rootfound=1;
            break; }
        else if(f1(a_0, a_1, a_2, a_3, a_4, a_5, x)==0) {                                                                       /*2η συνθήκη τερματισμού. Αν ο αλγόριθμος αποκλείνει τότε το πρόγραμμα εκτυπώνει nan και τερματίζει*/
            printf("nan\n");
            break; }
        else if(i>1000) {                                                                                                       /*3η συνθήκη τερματισμού. Αν ο μετρητής επαναλήψεων i ξεπεράσει το 1000, τότε το πρόγραμμα τερματίζει*/
            printf("incomplete\n");
            break; }
        
        x=x2;                                                                                                                   /*Η μεταβλητή x λαμβάνει την τιμή της προηγούμενης ρίζας (x2) ώστε να συνεχιστεί ο αλγόριθμος*/
        i++;                                                                                                                    /*Η μεταβλητή i αυξάνεται κάθε φορά κατά 1, ώστε να μετράει τον αριθμό επαναλήψεων*/
    } 
    
    if(rootfound==1) {                                                                                                          /*Αν βρεθεί ρίζα τότε εκτυπώνεται η τιμή της*/
        printf("%.2f\n", x2);
    }
    
    return 0;
}
