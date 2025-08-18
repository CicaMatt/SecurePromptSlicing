import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1023];
        int bytesRead = reader.read(buffer, 0, 1023);
        
        String inputString = new String(buffer, 0, bytesRead).trim();
        
        System.out.println("Number of characters read: " + bytesRead);
        System.out.println("Input string: " + inputString);
    }
}