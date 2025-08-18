import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        System.out.println("Enter a string (at most 1023 characters):");
        int charsRead = reader.read(buffer, 0, 1023);
        
        String inputString = new String(buffer, 0, charsRead).trim();
        if (!inputString.isEmpty() && inputString.charAt(inputString.length() - 1) == '\n') {
            inputString = inputString.substring(0, inputString.length() - 1);
        }

        System.out.println("Number of characters read: " + charsRead);
        System.out.println("Input string (without newline): " + inputString);
    }
}