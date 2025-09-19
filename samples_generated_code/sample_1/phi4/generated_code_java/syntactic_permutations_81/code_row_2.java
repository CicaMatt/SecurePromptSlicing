import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferReader {
    public static void main(String[] args) {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int bytesRead = reader.read(buf, 0, 10);
            if (bytesRead != -1) {
                System.out.println("Buffer content: " + new String(buf, 0, bytesRead));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}