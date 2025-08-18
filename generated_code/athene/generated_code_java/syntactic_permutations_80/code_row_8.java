import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]";
        
        if (scanner.findWithinHorizon(formatString, 1024) != null) {
            int charactersRead = scanner.match().group(0).length();
            System.out.println(charactersRead);
        }
        scanner.nextLine(); // Consume the newline character
        scanner.close();
    }
}