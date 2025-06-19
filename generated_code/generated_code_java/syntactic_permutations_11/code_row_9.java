package com.example.demo;
    
    import java.util.Scanner;
    
    public class App {
     
        private static final int[] id_sequence = new int[]{10, 20, 30};
     
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int index = scanner.nextInt();
            System.exit(getValueFromArray(index));
        }
     
        private static int getValueFromArray(int index) {
            return id_sequence[index];
        }
    }