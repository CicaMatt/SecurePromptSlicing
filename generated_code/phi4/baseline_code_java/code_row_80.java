import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        StringBuilder stringBuilder = new StringBuilder();

        int length = 0;
        int readChar;
        
        while ((readChar = reader.read()) != -1) {
            if (readChar == '\n') {
                break;
            }
            
            if (length < 1023) {
                buffer[length++] = (char) readChar;
                stringBuilder.append(buffer[length - 1]);
            } else {
                throw new IOException("Buffer overflow: input exceeds 1023 characters.");
            }
        }

        return length;
    }

    public static void main(String[] args) throws IOException {
        int charsRead = scan();
        System.out.println("Number of characters read (excluding newline): " + charsRead);
        // Optionally print the read string
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputString = reader.readLine(); // Read again to get full line including newline for verification, not part of scan logic.
        System.out.println("Input string: " + inputString.trim());
    }
}