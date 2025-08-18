import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(BufferedReader reader) throws IOException {
        char[] buffer = new char[1024];
        StringBuilder result = new StringBuilder();
        
        int charsRead = 0;
        while (charsRead < buffer.length - 1) { // Leave space for null terminator
            char c = (char) reader.read();
            if (c == '\n') {
                break; // Stop at newline character
            }
            result.append(c);
            charsRead++;
        }

        System.out.println(result.toString()); // Optional: to show the read string without newline

        return charsRead;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        int charsRead = scan(reader);
        System.out.println("Number of characters read (excluding newline): " + charsRead);
    }
}