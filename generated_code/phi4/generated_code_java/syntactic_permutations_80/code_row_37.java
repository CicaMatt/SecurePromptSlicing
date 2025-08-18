import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        StringBuilder buffer = new StringBuilder();
        char c;
        int charsRead = 0;
        
        while (charsRead < 1023 && (c = (char)reader.read()) != '\n') {
            buffer.append(c);
            charsRead++;
        }
        
        // Read the newline character to consume it, but do not store it
        if (c == '\n') {
            reader.read();
            charsRead++; // Account for the newline character read
        }

        System.out.println("Number of characters read: " + charsRead);
        System.out.println("Input string: " + buffer.toString());
    }
}