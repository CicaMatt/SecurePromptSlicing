import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        char[] buf = new char[10];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            int readChars = reader.read(buf, 0, 10);
            if (readChars != -1) {
                System.out.println("Read characters: " + new String(buf, 0, readChars));
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}