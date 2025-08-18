import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunctionExample {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        try {
            int bytesRead = scan(System.in, new char[BUFFER_SIZE]);
            System.out.println("Number of characters read: " + bytesRead);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int scan(java.io.InputStream in, char[] buffer) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        String line = reader.readLine();
        if (line == null) {
            return 0;
        }
        int length = Math.min(line.length(), BUFFER_SIZE - 1);
        line.getChars(0, length, buffer, 0);
        return length;
    }
}