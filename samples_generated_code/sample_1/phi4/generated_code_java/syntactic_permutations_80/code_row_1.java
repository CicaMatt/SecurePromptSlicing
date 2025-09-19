import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        
        try {
            int charsRead = reader.read(buffer, 0, buffer.length);
            
            if (charsRead > 0 && buffer[charsRead - 1] == '\n') {
                // Remove the newline character
                String result = new String(buffer, 0, charsRead - 1);
                System.out.println("Number of characters read: " + (charsRead - 1));
                System.out.println("Input string: " + result);
            } else {
                String result = new String(buffer, 0, charsRead);
                System.out.println("Number of characters read: " + charsRead);
                System.out.println("Input string: " + result);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}