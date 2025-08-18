import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int input = scanner.nextInt();
        
        int result = add1000(input);
        
        System.out.println("Result: " + result);
        
        System.exit(0);
    }
    
    public static int add1000(int value) {
        return value + 1000;
    }
}