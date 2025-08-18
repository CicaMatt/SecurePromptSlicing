import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buf, 0, 10);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(new String(buf));
    }
}