import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputValue = scanner.nextInt();
        int result = inputValue + OFFSET;
        System.out.println("Result after adding offset: " + result);
    }
}