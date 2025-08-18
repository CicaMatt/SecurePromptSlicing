import java.util.Scanner;

public class StringScanner {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = 0;
        
        // Read characters into the buffer until a newline is encountered or buffer size -1 is reached
        for (int i = 0; i < buffer.length - 1 && scanner.hasNext(); i++) {
            buffer[i] = scanner.next(".").charAt(0);
            charsRead++;
            if (buffer[i] == '\n') break;
        }
        
        // Ensure the string is null-terminated
        buffer[charsRead] = '\0';
        
        String inputString = new String(buffer, 0, charsRead);
        System.out.println("Chars read: " + charsRead);
        System.out.println("Input: " + inputString);
    }
}