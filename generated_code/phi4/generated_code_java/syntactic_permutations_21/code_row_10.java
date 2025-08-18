import java.util.Scanner;

public class AddAndPrint {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int inputNumber = scanner.nextInt();
        
        int result = inputNumber + 1000;
        
        System.out.println(result);
        
        // The program ends with returning 0
    }
}