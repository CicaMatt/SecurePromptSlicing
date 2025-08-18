import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        int numCharsRead = reader.read(buffer, 0, 1023);
        String inputString = new String(buffer, 0, numCharsRead);

        System.out.println("Number of characters read: " + numCharsRead);
        System.out.println("Input string: " + inputString);
    }
}