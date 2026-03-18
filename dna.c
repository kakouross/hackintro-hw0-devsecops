#include <stdio.h>
#include <stdlib.h>

FILE *file1, *file2;
int count1, count2, count1_new, count2_new, length, maxlength=0, maxi=0;
char *str1, *str2, c1, c2, *commonsequence;

int main(int argc, char *argv[]) {
    

//Αν δεν περαστούν δύο ορίσματα στην γραμμή εντολών
    if (argc != 3) { 
        fprintf(stderr, "Error: 2 arguments required. Usage: ./dna dnafile1 dnafile2\n");
        return 1;
    }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");

//Αν κάποιο από τα δύο αρχεία δεν μπορεί να ανοιχτεί
    if (file1 == NULL || file2 == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    fclose(file1);
    fclose(file2);

//εύερεση πλήθους χαρακτήρων κάθε αρχείου(αλυσίδας)
//1ο αρχείο
    file1 = fopen(argv[1], "r");
    //offset 0 και εντολή SEEK_END για να μετακινηθεί ο δείκτης του αρχείου στο τέλος του
    fseek(file1, 0, SEEK_END);
    //κλήση της ftell για να βρούμε τον αριθμό στοιχείων μέχρι τη θέση του δείκτη
    count1 = ftell(file1);
    //offset 0 και εντολή SEEK_SET για να μετακινηθεί ο δείκτης του αρχείου πίσω στην αρχή του
    fseek(file1, 0, SEEK_SET);
    fclose(file1);

//2ο αρχείο
    file2 = fopen(argv[2], "r");
    fseek(file2, 0, SEEK_END);
    count2 = ftell(file2);
    fseek(file2, 0, SEEK_SET);
    fclose(file2);

//μετατροπή αρχείου σε συμβολοσειρά
//1ο αρχείο
    str1 = malloc(count1 * sizeof(char));

    if (str1 == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    file1 = fopen(argv[1], "r");
    int i=0;
    count1_new=1;
    //μέσω της fgetc που διαβάζει κάθε φορά έναν χαρακτήρα από το αρχείο ο οποίος αποθηκεύεται στη c1
    while((c1 = fgetc(file1)) != EOF) {
        //περίπτωση αποδεκτών χαρακτήρων
        if(c1=='A' || c1=='C' || c1=='T' || c1=='G') {
            //αντιγραφή χαρακτήρα στη συμβολοσειρά
            str1[i] = c1;
            //αύξηση μετρητή
            i++;
            //αύξηση νέου πλήθους χαρακτήρων
            count1_new++;
        //περίπτωση μη αποδεκτών χαρακτήρων
        } else {
            //μείωση μεγέθους δεσμευμένης μνήμης μέσω realloc
            if(realloc(str1, count1-1 * sizeof(char)) == NULL) {
                fprintf(stderr, "Failed to resize memory.\n");
            }
            count1--;
        }
    }
    fclose(file1);

//Εκτελούμε την ίδια διαδικασία και για το 2ο αρχείο

    str2 = malloc(count2 * sizeof(char));

    if (str2 == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    file2 = fopen(argv[2], "r");
    int j=0; 
    count2_new=1;
    while((c2 = fgetc(file2)) != EOF) {
        if(c2=='A' || c2=='C' || c2=='T' || c2=='G') {
            str2[j] = c2;
            j++;
            count2_new++;
            } else {
                if(realloc(str2, count2-1 * sizeof(char)) == NULL) {
                    fprintf(stderr, "Failed to resize memory.\n");
                }
                count2--;
            }
    }
    fclose(file2);

//εύρεση μέγιστης κοινής αλυσίδας
    //σε κάθε επανάληψη επιλέγεται ένα στοιχείο της 1ης συμβολοσειράς
    for(int i=0; i<count1_new; i++) {
        //σε κάθε επανάληψη επιλέγεται ένα στοιχείο της 2ης συμβολοσειράς
        for(int j=0; j<count2_new; j++) {
            //μεταβλητές που αντικαθιστούν τις i,j 
            int m = 0;
            int n = 0;
            //αν δύο στοιχεία είναι ίδια ελέγχεται αν και τα αμέσως επόμενα είναι ίδια
            if(str1[i]==str2[j]) {
                //για να μην χαθούν οι τιμές των i,j χρησιμοποιύνται οι m,n
                m = i+1;
                n = j+1;
                //η μεταβλητή length κρατάει το μήκος της κοινής αλυσίδας
                length = 1;
                //ελέγχεται αν οι m,n είναι οι τελευταίες θέσεις της συμβολοσειράς για να μην κρασάρει το πρόγραμμα
                while(m<(count1_new-1) && n<(count2_new-1)) {
                    //αν και τα αμέσως επόμενα στοιχεία είναι ίδια συνεχίζεται η διαδικασία ελέγχου
                    if(str1[m]==str2[n]) {
                        m++;
                        n++;
                        length++;
                        if(length > maxlength) {
                            //η maxlength κρατάει το μήκος της μέγιστης κοινής αλυσίδας μέχρι εκείνη τη στιγμή
                            maxlength = length;
                            //η maxi κρατάει τη τιμή του πρώτου στοιχείου της μέγιστης κοινής αλυσίδας
                            maxi = i;
                        }
                    //αν τα αμέσως επόμενα στοιχεία δεν είναι ίδια η διαδικασία ελέγχου διακόπτεται
                    } else {
                        break;
                    }
                }
            }
        }
    }
//εκτύπωση των στοιχείων της μέγιστης κοινής συμβολοσειράς
    //δημιουργούμε τη συμβολοσειρά commonsequence στην οποία θα αντιγραφούν οι χαρακτήρες της μέγιστης κοινής αλυσίδας
    commonsequence = malloc(maxlength * sizeof(char));
    //ο πρώτος χαρακτήρας βρίσκεται στη θέση maxi και ο τελευταίος maxlength-1 θέσεις πιο μετά από τον πρώτο
    for(int i=maxi; i<(maxi+maxlength); i++) {
        commonsequence[i-maxi] = str1[i];
    }
    //βάζουμε τον κενό χαρακτήρα για να δηλώσουμε το τέλος της συμβολοσειράς
    commonsequence[maxlength]='\0';
    printf("%s\n", commonsequence);

    free(str1);
    free(str2);
    free(commonsequence);
    return 0;
}
