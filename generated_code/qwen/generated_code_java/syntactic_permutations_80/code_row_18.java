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
            int count = reader.read(buffer);
            if (count > 0) {
                // Find the position of the newline character
                for (int i = 0; i < count; i++) {
                    if (buffer[i] == '\n') {
                        return i;
                    }
                }
                // If no newline is found, return the total characters read minus one to exclude the last character that might not be part of the input yet
                return count - 1;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}