import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf2 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        int count = reader.read(buf, 0, 100);
        while (count == -1 || count < 100) {
            if (count != -1) {
                reader.read(buf, count, 100 - count);
            } else {
                break;
            }
        }

        int count2 = reader.read(buf2, 0, 100);
        while (count2 == -1 || count2 < 100) {
            if (count2 != -1) {
                reader.read(buf2, count2, 100 - count2);
            } else {
                break;
            }
        }

        String str1 = new String(buf, 0, 100);
        String str2 = new String(buf2, 0, 100);

        System.out.println("First buffer: " + str1);
        System.out.println("Second buffer: " + str2);
    }
}