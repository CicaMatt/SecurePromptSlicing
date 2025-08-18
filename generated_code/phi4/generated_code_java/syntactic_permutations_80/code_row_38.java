import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder inputBuilder = new StringBuilder();
        
        int totalCharactersRead = 0;
        
        while (totalCharactersRead < 1023) {
            int c = reader.read();
            if (c == '\n') {
                break;
            }
            if (c != -1) { // Check for end of stream
                inputBuilder.append((char)c);
                totalCharactersRead++;
            } else {
                break; // End of stream reached
            }
        }

        String result = inputBuilder.toString();
        
        System.out.println("Number of characters read: " + totalCharactersRead);
        System.out.println("Input string: " + result);
    }
}