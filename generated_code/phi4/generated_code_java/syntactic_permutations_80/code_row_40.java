import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format, char[] buffer) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputLine = reader.readLine();

        if (inputLine == null || !format.equals("%s\\n")) {
            return 0;
        }

        int length = inputLine.length();
        if (length > buffer.length - 1) {
            length = buffer.length - 1;
        }
        
        System.arraycopy(inputLine.toCharArray(), 0, buffer, 0, length);
        return length;
    }

    public static void main(String[] args) throws IOException {
        char[] buffer = new char[1024];
        int charsRead = scan("%s\\n", buffer);

        // Output the number of characters read
        System.out.println("Number of characters read: " + charsRead);
        
        // Print what was stored in the buffer (excluding null terminator)
        String result = new String(buffer, 0, charsRead);
        System.out.println("Buffer content: " + result);
    }
}