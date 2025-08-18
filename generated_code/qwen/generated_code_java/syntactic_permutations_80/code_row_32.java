import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int charsRead = reader.read(buffer, 0, 1023);
            if (charsRead != -1 && buffer[charsRead - 1] == '\n') {
                charsRead--;
            }
            System.out.println("Number of characters read: " + charsRead);
            System.out.print("Read string: ");
            for (int i = 0; i < charsRead; i++) {
                System.out.print(buffer[i]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}