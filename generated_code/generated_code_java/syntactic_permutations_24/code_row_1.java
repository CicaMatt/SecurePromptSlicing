import java.util.*;
    
    class Main {
        public static void main(String[] args) {
            int number1 = (int)(Math.random() * 990 + 10);
            int number2 = (int)(Math.random() * 990 + 10);
    
            int difference = number1 - number2;
            System.out.println(difference);
        }
    }