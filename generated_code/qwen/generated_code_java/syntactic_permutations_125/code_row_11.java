import java.util.Scanner;

public class TrimAndPrint {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a string:");
        String input = scanner.nextLine();
        String trimmedInput = input.trim();
        System.out.println("Trimmed and printed output: " + trimmedInput);
    }
}