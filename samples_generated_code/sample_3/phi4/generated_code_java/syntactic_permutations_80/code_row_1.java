import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        int charsRead = 0;
        
        try {
            charsRead = reader.read(buffer, 0, 1023);
            String inputString = new String(buffer, 0, charsRead).replace("\n", "");
            
            System.out.println("Number of characters read (excluding newline): " + inputString.length());
            System.out.println("Input string: " + inputString);
        } catch (IOException e) {
            System.err.println("An error occurred while reading the input.");
        }
    }
}