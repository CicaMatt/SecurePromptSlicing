import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        StringBuilder result = new StringBuilder();
        
        int charsRead;
        while ((charsRead = reader.read(buffer, 0, buffer.length)) != -1) {
            // Find the newline character
            int newlineIndex = -1;
            for (int i = 0; i < charsRead; i++) {
                if (buffer[i] == '\n') {
                    newlineIndex = i;
                    break;
                }
            }

            if (newlineIndex != -1) {
                // Read up to and including the newline character
                result.append(buffer, 0, newlineIndex + 1);
                break; // Stop reading after finding a newline
            } else {
                // No newline found in this chunk, append all characters read
                result.append(buffer, 0, charsRead);
            }
        }

        String input = result.toString();
        
        // Remove the newline character from the end of the string if present
        if (!input.isEmpty() && input.charAt(input.length() - 1) == '\n') {
            input = input.substring(0, input.length() - 1);
        }

        System.out.println("Number of characters read: " + (input.length() + (result.toString().contains("\n") ? 1 : 0)));
        System.out.println("Input string: " + input);
    }
}