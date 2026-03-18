#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(long long int p) {                                                                                      /*Συνάρτηση που ελέγχει αν ένας αριθμός είναι πρώτος*/                    
    if (p <= 3) {                                                                                                   /*Αν ο αριθμός είναι μικρότερος του 3, είναι πρώτος*/
        return 1;
    }

    if (p % 2 == 0 || p % 3 == 0) {                                                                                 /*Αν ο αριθμός διαιρείται με το 2 ή το 3 δεν είναι πρώτος*/
        return 0;
    }

    long long int i;
    for (i = 5; i <= sqrt(p); i += 6) {                                                                             /*Εξετάζονται μόνο οι αριθμοί που δεν είναι πολλαπλάσιοι του 2 ή του 3*/
        if (p % i == 0 || p % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}


int isPerfectSquare(double n) {                                                                                     /*Συνάρτηση που ελέγχει αν ένας αριθμός είναι τέλειο τετράγωνο πρώτου αριθμού*/
    if( (trunc(n) == n) && (isPrime(n) == 1) ) {                                                                    /*Αν η ρίζα του αριθμού είναι ακέραιος και πρώτος τότε είναι τέλειο τετράγωνο*/
        return 1;
    } else return 0;
}


long long int mirror(long long int m) {                                                                             /*Συνάρτηση που βρίσκει το κάτοπτρο ενός αριθμού*/
    long long int result = 0, tmp;
    
    while(m > 0) {
        tmp = m % 10;                                                                                               /*tmp = τελευταίο ψηφίο του αριθμού*/
        result = 10 * result + tmp;                                                                                 /*result = προστίθεται κάθε φορά το τελευταίο ψηφίο του αρχικού αριθμού*/
        m /= 10;                                                                                                    /*Ο αρχικός αριθμός μειώνεται κατά ένα ψηφίο*/
    }
    
    return result;
}

 long long int j;
 long long int sum=0;
 long long int low;
 long long int high;


int main(int argc, char **argv) {
    if(argc != 3) {                                                                                                 /*Αν το πρόγραμμα δεν δέχεται δύο ορίσματα εμφανίζεται κατάλληλο μήνυμα*/
        printf("2 numbers required\n");
        return 1;
    }

    long long int low = atoll(argv[1]);
    long long int high = atoll(argv[2]);

    if(low>high || low<1 || low>1e15 || high <1 || high >1e15) {                                                    /*Έλεγχος εγκυρότητας των ορισμάτων που δώθηκαν*/
        return 1;
    }

    long long int sqlow = sqrt(low);                                                                                /*Δημιουργία μεταβλητών που περιέχουν τη ρίζα των ορισμάτων για βελτιστοποίηση του αλγορίθμου*/
    long long int sqhigh = sqrt(high);

    for(j = ceil(sqlow); j <= sqhigh; j++) {                                                                        /*Έλεγχος για το αν ένας αριθμός είναι κατοπτρικό πρώτο τετράγωνο*/
        if( (isPerfectSquare(j) == 1) && (isPerfectSquare(sqrt(mirror(j*j))) == 1) && (mirror(j*j) != j*j) ) { 
            sum += j*j; 
        }
    }

    printf("%lld\n", sum);
    return 0;
}
