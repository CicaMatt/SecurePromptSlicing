import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buf, 0, 100);
            reader.read(buf1, 0, 100);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}