import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a value: ");
        int input = scanner.nextInt();
        
        final int OFFSET = 1000;
        int result = input + OFFSET;
        
        System.out.println("Result after adding offset of " + OFFSET + ": " + result);
    }
}