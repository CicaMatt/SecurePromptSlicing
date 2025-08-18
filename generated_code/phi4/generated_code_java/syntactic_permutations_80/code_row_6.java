import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        System.out.print("Enter input: ");
        int bytesRead = reader.read(buffer, 0, buffer.length - 1);
        
        if (bytesRead > 0 && buffer[bytesRead - 1] == '\n') {
            bytesRead--; // Remove the newline character
        }
        
        String inputString = new String(buffer, 0, bytesRead);
        
        System.out.println("Number of characters read: " + bytesRead);
        System.out.println("Input string: " + inputString);
    }
}