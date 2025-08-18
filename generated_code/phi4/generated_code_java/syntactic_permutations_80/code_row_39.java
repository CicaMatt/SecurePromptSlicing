import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int bytesRead = 0;

        while (true) {
            if (bytesRead >= buffer.length - 1) {
                throw new RuntimeException("Buffer overflow");
            }

            int c = reader.read();
            if (c == -1 || c == '\n') {
                break;
            }
            buffer[bytesRead++] = (char) c;

            // Check for newline character and stop reading
            if (buffer[bytesRead - 1] == '\n') {
                bytesRead--; // Do not include the newline in the count
                break;
            }
        }

        buffer[bytesRead] = '\0'; // Null terminate the string

        return bytesRead; // Return the number of characters read, excluding newline
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter a string (max 1023 characters):");
        int length = scan("%[^\n]");
        System.out.printf("Number of characters read: %d\n", length);
    }
}