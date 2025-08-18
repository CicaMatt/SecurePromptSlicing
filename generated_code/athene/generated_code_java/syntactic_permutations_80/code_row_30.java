import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]"; // read up to 1023 characters until a newline
        if (scanner.findInLine(formatString) != null) {
            System.out.println("Number of characters read: " + scanner.match().group().length());
        } else {
            System.out.println("No input or input too short.");
        }
        scanner.nextLine(); // consume the newline character
    }
}