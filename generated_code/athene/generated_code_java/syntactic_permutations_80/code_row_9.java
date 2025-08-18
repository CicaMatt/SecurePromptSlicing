import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]";
        
        if (scanner.findWithinHorizon(formatString, 1024) != null) {
            String input = scanner.match().group();
            System.out.println("Characters read: " + input.length());
        } else {
            System.out.println("No characters read");
        }
        scanner.nextLine(); // Consume newline left-over
        scanner.close();
    }
}