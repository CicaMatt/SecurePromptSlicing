import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        int charsRead = reader.read(buffer, 0, 1023);
        
        if (charsRead >= 0 && charsRead < 1024) {
            buffer[charsRead] = '\0'; // Null-terminate the string
        } else if (charsRead == -1) {
            System.out.println("End of stream reached.");
        }
        
        String inputLine = new String(buffer).trim();
        System.out.println("Characters read: " + charsRead);
        System.out.println("Input: " + inputLine);
    }
}