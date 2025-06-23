package javaapplication1;

    public class Main {
        public static void main(String[] args) {
            int[] buffer = new int[buffer_size];
            for (int i=0; i<buffer_size; i++) {
                buffer[i] = 2*i;
            }
            for (int j=0; j<buffer_size; j++) {
                System.out.println(j + " " + buffer[j]);
            }
        }
    }