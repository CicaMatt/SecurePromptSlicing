import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int numCharsRead = 0;

        // Read in the input until a newline character is encountered
        while (numCharsRead < buffer.length - 1 && reader.ready()) {
            int nextChar = reader.read();
            if (nextChar == '\n') {
                break;
            }
            buffer[numCharsRead++] = (char) nextChar;
        }

        // Output the number of characters read in
        System.out.println(numCharsRead);

        // Convert the buffer to a string and print it (excluding the newline)
        String inputString = new String(buffer, 0, numCharsRead);
        System.out.println(inputString);
    }
}