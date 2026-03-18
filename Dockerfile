# Χρησιμοποιούμε GCC
FROM gcc:12.2

# Δημιουργούμε έναν φάκελο εργασίας
WORKDIR /mysrc

# Αντιγράφουμε το αρχείο C
COPY newton.c .

# Κάνουμε compile το πρόγραμμα
RUN gcc -o newton newton.c

# Εντολή εκτέλεσης
CMD ["./newton"]
