import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter a number: ");
        int number = scanner.nextInt();
        
        int result = number + 1000;
        
        System.out.println("The result is: " + result);
        
        // Since this is a main method, it implicitly returns 0 if the program exits without errors.
    }
}