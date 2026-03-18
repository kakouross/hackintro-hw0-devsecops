# Χρησιμοποιούμε GCC
FROM gcc:12.2

# Δημιουργούμε έναν φάκελο εργασίας
WORKDIR /mysrc

# Αντιγράφουμε το αρχείο C
COPY dna.c .

# Κάνουμε compile το πρόγραμμα
RUN gcc -o dna dna.c

# Εντολή εκτέλεσης
CMD ["./dna"]
