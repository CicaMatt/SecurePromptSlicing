import java.util.Scanner;

public class ScannerExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]";
        
        if (scanner.findWithinHorizon(formatString, 1024) != null) {
            String input = new String(buffer).trim();
            System.out.println("Number of characters read: " + input.length());
        } else {
            System.out.println("No input or input too large.");
        }
        
        scanner.close();
    }
}