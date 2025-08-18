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
        char[] buffer = new char[1024];
        try {
            int charsRead = reader.read(buffer, 0, 1024);
            if (charsRead > 0) {
                for (int i = 0; i < charsRead; i++) {
                    if (buffer[i] == '\n') {
                        return i;
                    }
                }
                return charsRead;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }
}