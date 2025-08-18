import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ReadString {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        int numberOfCharsRead = reader.read(buffer, 0, 1023);
        
        if (numberOfCharsRead > 0 && buffer[numberOfCharsRead - 1] == '\n') {
            numberOfCharsRead--; // Remove the newline character
        }
        
        String inputString = new String(buffer, 0, numberOfCharsRead);
        
        System.out.println("Number of characters read: " + numberOfCharsRead);
        System.out.println("Input string: " + inputString);
    }
}