import java.util.Scanner;

public class OffsetAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int inputValue = scanner.nextInt();
        
        final int OFFSET = 1000;
        int result = inputValue + OFFSET;
        
        System.out.println("The value after adding the offset is: " + result);
        
        scanner.close();
    }
}