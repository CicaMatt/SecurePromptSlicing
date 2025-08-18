import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int count = reader.read(buf, 0, 100);
            if (count != -1) {
                reader.read(buf1, 0, 100);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}