import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int length = 0;

        try {
            String input = reader.readLine();
            if (input != null && input.length() > 0) {
                length = Math.min(input.length(), buffer.length - 1);
                input.getChars(0, length, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Number of characters read: " + length);
    }
}