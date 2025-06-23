import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = new int[]{1, 2, 3};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        if (scanner.hasNextInt()) {
            int userInput = scanner.nextInt();
            int sequenceIdx = id_sequence[userInput];
            System.out.printf("Value at index %d is: %d", userInput, sequenceIdx);
        } else {
            System.out.println("Invalid input! Enter a number.");
        }
    }
}