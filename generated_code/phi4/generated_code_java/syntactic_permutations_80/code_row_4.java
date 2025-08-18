import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        // Read input until a newline character is encountered
        int charsRead = reader.read(buffer, 0, 1023);
        
        // Find the position of the newline character
        int newlineIndex = -1;
        for (int i = 0; i < charsRead; i++) {
            if (buffer[i] == '\n') {
                newlineIndex = i;
                break;
            }
        }
        
        // If a newline was found, adjust the number of characters read
        if (newlineIndex != -1) {
            charsRead = newlineIndex;
        } else {
            // If no newline was found within 1023 characters, assume end of input
        }
        
        // Convert buffer to string and print the result
        String result = new String(buffer, 0, charsRead);
        System.out.println(result);

        // Print number of characters read (excluding newline)
        System.out.println(charsRead);
    }
}