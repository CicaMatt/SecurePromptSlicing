import java.util.Scanner;

public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        int inputValue = scanner.nextInt();

        int result = inputValue + OFFSET;

        System.out.println("The value after adding the offset is: " + result);
    }
}