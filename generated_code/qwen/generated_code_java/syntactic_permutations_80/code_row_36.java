import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int bytesRead = scan(new char[1024]);
        System.out.println("Number of characters read: " + bytesRead);
    }

    public static int scan(char[] buffer) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input != null) {
                int length = Math.min(input.length(), buffer.length - 1);
                input.getChars(0, length, buffer, 0);
                return length;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}