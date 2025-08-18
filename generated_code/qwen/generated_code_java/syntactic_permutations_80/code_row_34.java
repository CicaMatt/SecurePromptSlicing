import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunctionExample {
    public static void main(String[] args) {
        try {
            int charactersRead = scan();
            System.out.println("Number of characters read: " + charactersRead);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int scan() throws IOException {
        char[] buffer = new char[1024];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputLine = reader.readLine(); // Reads a line until newline character
        if (inputLine != null) {
            int length = Math.min(inputLine.length(), 1023); // Ensure we don't exceed buffer size - 1 for newline
            inputLine.getChars(0, length, buffer, 0);
            return length;
        }
        return 0; // Return 0 if no line was read
    }
}