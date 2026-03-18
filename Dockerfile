# Χρησιμοποιούμε GCC
FROM alpine

# Εγκαθιστούμε τον gcc και τις βιβλιοθήκες
RUN apk add gcc make git linux-headers musl-dev

# Δημιουργούμε έναν φάκελο εργασίας
WORKDIR /mysrc

# Αντιγράφουμε το αρχείο C
COPY newton.c .

# Κάνουμε compile το πρόγραμμα
RUN gcc -o newton newton.c

# Εντολή εκτέλεσης
CMD ["./newton"]
