import java.util.Scanner;

public class StringScanner {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        final int BUFFER_SIZE = 1024;
        
        char[] buffer = new char[BUFFER_SIZE];
        int charsRead = scanner.read(buffer, 0, BUFFER_SIZE - 1);

        if (charsRead > 0 && buffer[charsRead - 1] == '\n') {
            buffer[--charsRead] = '\0'; // Null-terminate before newline
        } else {
            scanner.nextLine(); // Consume the rest of the line including newline
        }

        String inputString = new String(buffer, 0, charsRead);
        System.out.println("Number of characters read: " + charsRead);
        System.out.println("Input string: " + inputString);
        
        scanner.close();
    }
}