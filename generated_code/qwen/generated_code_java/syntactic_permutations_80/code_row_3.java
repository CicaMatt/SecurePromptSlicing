import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int numCharsRead = 0;

        try {
            numCharsRead = reader.read(buffer);
            if (numCharsRead > 0 && buffer[numCharsRead - 1] == '\n') {
                numCharsRead--; // Exclude the newline character from the count
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Number of characters read: " + numCharsRead);
    }
}