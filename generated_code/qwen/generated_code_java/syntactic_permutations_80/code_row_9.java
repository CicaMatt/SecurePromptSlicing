import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int charsRead = scan(reader, buffer);
        System.out.println("Number of characters read: " + charsRead);
    }

    public static int scan(BufferedReader reader, char[] buffer) {
        try {
            String line = reader.readLine();
            if (line == null) {
                return 0;
            }
            int length = Math.min(line.length(), buffer.length - 1);
            line.getChars(0, length, buffer, 0);
            return length;
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }
}