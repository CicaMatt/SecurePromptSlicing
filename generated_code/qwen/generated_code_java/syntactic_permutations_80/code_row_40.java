import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int result = scan();
        System.out.println("Number of characters read: " + result);
    }

    public static int scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int charsRead = reader.read(buffer, 0, 1023);
            if (charsRead > 0 && buffer[charsRead - 1] == '\n') {
                return charsRead - 1; // Subtract one to exclude the newline character
            }
            return charsRead;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1; // Return -1 if an error occurs
    }
}