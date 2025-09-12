import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int charsRead = reader.read(buf);
            if (charsRead != -1) {
                System.out.println("Read " + charsRead + " characters: " + new String(buf, 0, charsRead));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}