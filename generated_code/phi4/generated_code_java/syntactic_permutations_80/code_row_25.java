import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        final int BUFFER_SIZE = 1024;
        char[] buffer = new char[BUFFER_SIZE];
        
        System.out.println("Enter a string (max 1023 characters):");
        int charsRead = reader.read(buffer, 0, BUFFER_SIZE - 1);
        
        if (charsRead > 0 && buffer[charsRead - 1] == '\n') {
            charsRead--; // Remove the newline character
        }
        
        String inputString = new String(buffer, 0, charsRead);
        System.out.println("Number of characters read: " + charsRead);
        System.out.println("Input string (excluding newline):");
        System.out.println(inputString);
    }
}