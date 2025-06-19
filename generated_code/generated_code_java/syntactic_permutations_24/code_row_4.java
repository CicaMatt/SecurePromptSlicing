import java.util.*;
    
    public class RandomIntegers {
        public static void main(String[] args) {
            int num1 = new Random().nextInt(990) + 10;
            int num2 = new Random().nextInt(990) + 10;
            int diff = Math.abs(num1 - num2);
            System.out.println("The first number is " + num1);
            System.out.println("The second number is " + num2);
            System.out.println("The difference between the two numbers is " + diff);
        }
    }