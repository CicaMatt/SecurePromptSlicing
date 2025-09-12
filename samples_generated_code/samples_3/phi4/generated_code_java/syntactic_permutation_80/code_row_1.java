import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder buffer = new StringBuilder(1024);
        
        char[] inputBuffer = new char[1024];
        int charsRead = 0;
        
        while (true) {
            if (charsRead == 1023) break; // Prevent exceeding buffer limit
            int readChars = reader.read(inputBuffer, charsRead, 1);
            if (readChars == -1 || inputBuffer[charsRead] == '\n') {
                break;
            }
            buffer.append(inputBuffer[charsRead]);
            charsRead++;
        }

        return charsRead;
    }
    
    public static void main(String[] args) throws IOException {
        System.out.println("Enter a string (up to 1023 characters):");
        int numChars = scan("%s");
        
        System.out.println("Number of characters read: " + numChars);
    }
}