import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        int charsRead = reader.read(buffer, 0, 1023);
        
        String input = new String(buffer, 0, charsRead).trim();
        
        System.out.println("Number of characters read: " + input.length());
        System.out.println("Input string: " + input);
    }
}