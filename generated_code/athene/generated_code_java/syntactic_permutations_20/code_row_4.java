import java.util.Scanner;

public class OffsetValue {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int value = scanner.nextInt();
        int result = value + OFFSET;
        System.out.println("Result after adding offset: " + result);
    }
}