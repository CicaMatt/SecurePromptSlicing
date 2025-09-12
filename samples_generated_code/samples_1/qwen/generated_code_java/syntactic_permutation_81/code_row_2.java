import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferReaderExample {
    public static void main(String[] args) {
        char[] buf = new char[10];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            reader.read(buf, 0, 10);
            System.out.println("Read characters: " + new String(buf));
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