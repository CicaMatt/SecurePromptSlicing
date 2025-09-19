import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        int number = scanner.nextInt();

        int result = number + 1000;
        
        System.out.println("The value after adding 1000 is: " + result);
        
        System.exit(0);
    }
}