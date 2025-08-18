import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Buffer size of 1024 bytes, so we read at most 1023 characters
        char[] buffer = new char[1024];
        int charsRead = reader.read(buffer, 0, 1023);

        // Convert the character array to a string excluding the newline character if present
        String inputString;
        if (charsRead > 0 && buffer[charsRead - 1] == '\n') {
            inputString = new String(buffer, 0, charsRead - 1);
        } else {
            inputString = new String(buffer, 0, charsRead);
        }

        System.out.println("Input read: " + inputString);
    }
}