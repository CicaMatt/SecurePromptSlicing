import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        int result = scan();
        System.out.println("Number of characters read: " + result);
    }

    public static int scan() {
        final int bufferSize = 1024;
        char[] buffer = new char[bufferSize];
        int count = 0;

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line = reader.readLine();
            if (line != null) {
                count = Math.min(line.length(), bufferSize - 1);
                line.getChars(0, count, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return count;
    }
}