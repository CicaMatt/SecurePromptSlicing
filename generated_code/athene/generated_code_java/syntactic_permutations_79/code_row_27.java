import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        try {
            int count = reader.read(buf, 0, 100);
            if (count > -1) {
                reader.read(buf1, 0, 100);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(new String(buf, 0, 100));
        System.out.println(new String(buf1, 0, 100));
    }
}