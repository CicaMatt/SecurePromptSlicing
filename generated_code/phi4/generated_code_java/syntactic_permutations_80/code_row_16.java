import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format, StringBuilder buffer) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            String inputLine = br.readLine();
            
            if (inputLine == null || !format.equals("%s")) {
                return -1;
            }
            
            // Remove the trailing newline character
            if (buffer.length() > 0 && buffer.charAt(buffer.length() - 1) == '\n') {
                buffer.setLength(buffer.length() - 1);
            }

            int charsRead = inputLine.length();
            if (charsRead + 1 < buffer.capacity()) { // +1 for the null terminator
                buffer.append(inputLine);
                return charsRead;
            } else {
                return -1; // Indicate failure due to buffer overflow
            }
        } catch (Exception e) {
            return -1; // Indicate an error occurred
        }
    }

    public static void main(String[] args) {
        StringBuilder buffer = new StringBuilder(1024);
        int charsRead = scan("%s", buffer);

        if (charsRead >= 0) {
            System.out.println("Characters read: " + charsRead);
            System.out.println("Buffer content: " + buffer.toString());
        } else {
            System.out.println("Error reading input.");
        }
    }
}