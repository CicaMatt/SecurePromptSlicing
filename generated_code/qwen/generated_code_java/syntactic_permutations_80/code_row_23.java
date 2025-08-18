import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScannerExample {
    public static void main(String[] args) {
        int bytesRead = scan();
        System.out.println("Number of characters read: " + bytesRead);
    }

    public static int scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int bytesRead = reader.read(buffer, 0, 1023);
            if (bytesRead > 0 && buffer[bytesRead - 1] == '\n') {
                bytesRead--;
            }
            return bytesRead;
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }
}