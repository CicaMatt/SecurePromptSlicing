import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int count = reader.read(buf, 0, 100);
            if (count > 0) {
                System.out.println("First buffer: " + new String(buf, 0, Math.min(count, 100)));
            }
            
            count = reader.read(buf1, 0, 100);
            if (count > 0) {
                System.out.println("Second buffer: " + new String(buf1, 0, Math.min(count, 100)));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}