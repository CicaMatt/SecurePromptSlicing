import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        int charsRead = reader.read(buffer, 0, buffer.length);
        if (charsRead > 0 && buffer[charsRead - 1] == '\n') {
            charsRead--; // Do not include the newline character
        }

        String input = new String(buffer, 0, charsRead);
        
        System.out.println("Number of characters read: " + charsRead);
        System.out.println("Input string: " + input);
    }
}