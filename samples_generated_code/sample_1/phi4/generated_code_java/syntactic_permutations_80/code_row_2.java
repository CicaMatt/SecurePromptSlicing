import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        System.out.println("Enter a string (up to 1023 characters, ending with newline):");
        
        int numberOfCharactersRead = reader.read(buffer);
        
        if (numberOfCharactersRead > 0) {
            // Ensure the last character is not included if it's a newline
            if (buffer[numberOfCharactersRead - 1] == '\n') {
                numberOfCharactersRead--;
            }
            
            String result = new String(buffer, 0, numberOfCharactersRead);
            System.out.println("Number of characters read: " + numberOfCharactersRead);
            System.out.println("String read: " + result);
        } else {
            System.out.println("No input was read.");
        }
    }
}