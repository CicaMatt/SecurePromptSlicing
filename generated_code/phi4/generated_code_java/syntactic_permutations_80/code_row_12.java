import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        try {
            if (format.equals("%s\n")) {
                String line = reader.readLine();
                if (line != null && !line.isEmpty()) {
                    int length = Math.min(line.length(), 1023);
                    for (int i = 0; i < length; i++) {
                        buffer[i] = line.charAt(i);
                    }
                    return length;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public static void main(String[] args) {
        System.out.println("Enter a string:");
        int charactersRead = scan("%s\n");
        System.out.println("Number of characters read: " + charactersRead);
    }
}