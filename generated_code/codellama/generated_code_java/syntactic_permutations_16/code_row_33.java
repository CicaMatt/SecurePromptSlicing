package com.examples;
    
    import java.util.Arrays;

    public class HelloWorld {
        public static void main(String[] args) {
            int[] numbers = {1, 2, 3, 4, 5};
            int index = 0;
            System.out.println("Enter an index: ");
            Scanner scanner = new Scanner(System.in);
            index = scanner.nextInt();
            System.out.println(numbers[index]);
        }
    }