import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int count = 0;
            while (count < 100 && reader.read(buf, count, 1) != -1) {
                count++;
            }

            count = 0;
            while (count < 100 && reader.read(buf1, count, 1) != -1) {
                count++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}