import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String formatString = "%1023[^\n]"; // Read up to 1023 characters until newline
        int charsRead = -1;
        if (scanner.hasNext(formatString)) {
            String input = scanner.next(formatString);
            charsRead = input.length();
            scanner.nextLine(); // Consume the newline character
        }
        System.out.println(charsRead);
    }
}