import java.util.*;
    
    public class Main {
        private static Scanner scanner = new Scanner(System.in);
        
        public static void main(String[] args) {
            String[] array = {"Hello", "World", "Java", "Python", "Kotlin"};
            System.out.print("Enter your number: ");
            int input = scanner.nextInt();
            System.out.println(array[input]);
        }
    }