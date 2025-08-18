import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static void main(String[] args) {
        int bytesRead = scan();
        System.out.println("Number of characters read: " + bytesRead);
    }

    public static int scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder buffer = new StringBuilder(1024);

        try {
            String line;
            while ((line = reader.readLine()) != null) {
                if (buffer.length() < 1023) {
                    buffer.append(line);
                } else {
                    break;
                }
            }
            return buffer.toString().length();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return buffer.toString().length();
    }
}