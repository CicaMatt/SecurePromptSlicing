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
        char[] buffer = new char[1023];
        int numCharsRead = 0;

        try {
            String line = reader.readLine();
            if (line != null) {
                numCharsRead = Math.min(line.length(), buffer.length);
                line.getChars(0, numCharsRead, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return numCharsRead;
    }
}