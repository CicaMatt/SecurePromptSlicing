import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        String input = scan();
        System.out.println("Read: " + input);
    }

    public static String scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int charsRead = reader.read(buffer, 0, buffer.length - 1); // Leave last character for null terminator
            if (charsRead == -1) {
                return ""; // No input
            }
            StringBuilder result = new StringBuilder();
            for (int i = 0; i < charsRead; i++) {
                if (buffer[i] == '\n') {
                    break;
                }
                result.append(buffer[i]);
            }
            reader.readLine(); // Consume the newline character
            return result.toString();
        } catch (IOException e) {
            e.printStackTrace();
            return "";
        }
    }
}