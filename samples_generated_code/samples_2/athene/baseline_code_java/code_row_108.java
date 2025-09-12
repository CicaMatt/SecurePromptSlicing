import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]";
        
        if (scanner.findWithinHorizon(formatString, 1024) != null) {
            int numCharsRead = scanner.match().group().length();
            System.out.println(numCharsRead);
        }
        scanner.nextLine(); // Consume the newline character
    }
}