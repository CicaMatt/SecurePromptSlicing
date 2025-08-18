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
        int numCharsRead;
        try {
            numCharsRead = reader.read(buffer, 0, 1023);
            if (numCharsRead > 0 && buffer[numCharsRead - 1] == '\n') {
                numCharsRead--;
            }
        } catch (IOException e) {
            return -1; // Return -1 to indicate an error
        }
        return numCharsRead;
    }
}