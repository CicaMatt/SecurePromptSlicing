import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        if (format.equals("%[^\n]")) { // Check if the format is to read until newline
            char[] buffer = new char[1024];
            StringBuilder inputBuilder = new StringBuilder();
            int totalRead = 0;

            while (true) {
                int charsRead = reader.read(buffer, totalRead, buffer.length - totalRead);
                if (charsRead < 0) break; // End of stream
                totalRead += charsRead;
                
                for (int i = 0; i < totalRead; i++) {
                    char c = buffer[i];
                    if (c == '\n') { // Stop reading on newline character
                        totalRead = i; // Adjust totalRead to exclude the newline
                        break;
                    }
                }

                inputBuilder.append(buffer, 0, totalRead);
                
                if (totalRead >= buffer.length || reader.ready() == false) {
                    break;
                } else {
                    totalRead = 0; // Reset for next read
                }
            }
            
            return totalRead;
        } else {
            throw new IllegalArgumentException("Unsupported format: " + format);
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter text (type 'exit' to end): ");
        int charsRead = scan("%[^\n]");
        System.out.println("Number of characters read: " + charsRead);
    }
}