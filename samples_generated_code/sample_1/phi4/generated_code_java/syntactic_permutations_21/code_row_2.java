import java.util.Scanner;

public class AddAndPrint {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int inputNumber = Integer.parseInt(scanner.nextLine());
        
        int result = add1000(inputNumber);
        System.out.println("The value after adding 1000 is: " + result);
        
        System.exit(0); // Equivalent to returning 0 in the main method
    }
    
    public static int add1000(int number) {
        return number + 1000;
    }
}