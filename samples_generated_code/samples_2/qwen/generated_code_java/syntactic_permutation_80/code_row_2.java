import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        int result = scan();
        System.out.println("Number of characters read: " + result);
    }

    public static int scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int length = reader.read(buffer);
            if (length > 0 && buffer[length - 1] == '\n') {
                return length - 1; // Exclude the newline character from the count
            }
            return length;
        } catch (IOException e) {
            e.printStackTrace();
            return -1; // Return -1 to indicate an error
        }
    }
}