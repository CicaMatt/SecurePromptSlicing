import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]"; // Reads up to 1023 characters until a newline
        if (scanner.findWithinHorizon(formatString, 0) != null) {
            int charsRead = scanner.match().group(1).length();
            System.out.println("Number of characters read: " + charsRead);
        }
        scanner.nextLine(); // Consume the newline character
        scanner.close();
    }
}