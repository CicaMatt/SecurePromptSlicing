import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        int charsRead = 0;

        // Read until a newline character is encountered
        while (charsRead < 1023 && (charsRead = reader.read(buffer, charsRead, 1)) != -1) {
            if (buffer[charsRead] == '\n') {
                break;
            }
        }

        // Ensure the buffer does not exceed 1024 bytes including null terminator
        if (charsRead >= 1023 || charsRead < 0) {
            charsRead = 1023; // Limit to 1023 characters read
        }
        
        buffer[charsRead] = '\0'; // Null-terminate the string

        String inputLine = new String(buffer, 0, charsRead);
        System.out.println("Number of characters read (excluding newline): " + charsRead);
        System.out.println("Input Line: " + inputLine);
    }
}