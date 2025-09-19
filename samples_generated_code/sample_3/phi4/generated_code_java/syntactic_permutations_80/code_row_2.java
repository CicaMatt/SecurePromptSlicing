import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanExample {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        // Read until newline, excluding the newline character
        int bytesRead = reader.read(buffer, 0, buffer.length - 1);
        
        if (bytesRead > 0) {
            // Ensure null termination of string
            buffer[bytesRead] = '\0';
            
            // Convert char array to String, ignoring the extra space for newline
            String inputString = new String(buffer, 0, bytesRead).trim();
            
            System.out.println("Characters read: " + bytesRead);
            System.out.println("Input String: " + inputString);
        } else {
            System.out.println("No characters were read.");
        }
    }
}