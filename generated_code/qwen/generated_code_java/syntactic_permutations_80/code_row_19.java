import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        try {
            int result = scan();
            System.out.println("Number of characters read: " + result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int scan() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[BUFFER_SIZE];
        int numCharsRead = reader.read(buffer, 0, BUFFER_SIZE - 1);
        if (numCharsRead > 0) {
            // Find the newline character and adjust the count
            for (int i = 0; i < numCharsRead; i++) {
                if (buffer[i] == '\n') {
                    return i;
                }
            }
        }
        return numCharsRead;
    }
}