import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            int charsRead = scan(reader, buffer);
            System.out.println("Number of characters read: " + charsRead);
            System.out.print("Buffer content: ");
            for (int i = 0; i < charsRead; i++) {
                System.out.print(buffer[i]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int scan(BufferedReader reader, char[] buffer) throws IOException {
        String line = reader.readLine();
        if (line == null) {
            return 0;
        }
        int length = Math.min(line.length(), buffer.length - 1);
        line.getChars(0, length, buffer, 0);
        return length;
    }
}