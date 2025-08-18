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
            String input = reader.readLine();
            if (input == null) return 0;
            int length = Math.min(input.length(), buffer.length - 1);
            input.getChars(0, length, buffer, 0);
            return length;
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }
}