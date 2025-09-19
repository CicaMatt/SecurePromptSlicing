import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int bytesRead = scan();
        System.out.println("Number of characters read: " + bytesRead);
    }

    public static int scan() {
        char[] buffer = new char[1024];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line = reader.readLine();
            if (line != null) {
                int length = Math.min(line.length(), 1023);
                line.getChars(0, length, buffer, 0);
                return length;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}