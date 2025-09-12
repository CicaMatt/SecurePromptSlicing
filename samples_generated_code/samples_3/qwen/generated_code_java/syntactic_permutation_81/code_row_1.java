import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocator {
    public static void main(String[] args) {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buf);
            System.out.println("Read characters: " + new String(buf));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}