import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        int count = reader.read(buf, 0, 100);
        while (count == -1 || count < 100) {
            if (count != -1) {
                reader.read(buf, count, 100 - count);
            } else {
                break;
            }
        }

        int count1 = reader.read(buf1, 0, 100);
        while (count1 == -1 || count1 < 100) {
            if (count1 != -1) {
                reader.read(buf1, count1, 100 - count1);
            } else {
                break;
            }
        }

        reader.close();
    }
}