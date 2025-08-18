import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        int result = scan();
        System.out.println("Number of characters read: " + result);
    }

    public static int scan() {
        char[] buffer = new char[1024];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null) {
                int length = Math.min(input.length(), 1023);
                for (int i = 0; i < length; i++) {
                    buffer[i] = input.charAt(i);
                }
                return length;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}