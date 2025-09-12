import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunctionExample {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int charsRead = 0;

        try {
            String line = reader.readLine();
            if (line != null) {
                charsRead = Math.min(line.length(), buffer.length - 1);
                line.getChars(0, charsRead, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Number of characters read: " + charsRead);
    }
}