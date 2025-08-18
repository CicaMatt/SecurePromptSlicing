import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        int bytesRead = reader.read(buffer, 0, 1023);
        String input = new String(buffer, 0, bytesRead);

        System.out.println("Number of characters read: " + bytesRead);
        System.out.println("Input (without newline): " + input.trim());
    }
}