import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        if (format.equals("%[^\n]%c")) {
            char[] buffer = new char[1024];
            StringBuilder sb = new StringBuilder();
            
            int bytesRead;
            while ((bytesRead = reader.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    if (buffer[i] == '\n') {
                        // Consume the newline character
                        continue;
                    }
                    sb.append(buffer[i]);
                    
                    // Stop reading after newline is detected
                    if (sb.length() >= 1023) break;
                }
                
                // Break out of the loop if we have read at least one line
                if (bytesRead > 0 && buffer[bytesRead - 1] == '\n') {
                    break;
                }
            }

            String input = sb.toString();
            return input.length();
        } else {
            throw new IllegalArgumentException("Unsupported format string");
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter a string (up to 1023 characters, followed by newline): ");
        int count = scan("%[^\n]%c");
        System.out.println("Number of characters read: " + count);
    }
}