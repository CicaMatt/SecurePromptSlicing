import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        try {
            // First buffer allocation
            char[] buf1 = new char[1024];
            int charsRead1 = reader.read(buf1, 0, 100);
            if (charsRead1 > 0) {
                String str1 = new String(buf1, 0, Math.min(charsRead1, 100));
                System.out.println("First buffer content: " + str1);
            }

            // Second buffer allocation
            char[] buf2 = new char[1024];
            int charsRead2 = reader.read(buf2, 0, 100);
            if (charsRead2 > 0) {
                String str2 = new String(buf2, 0, Math.min(charsRead2, 100));
                System.out.println("Second buffer content: " + str2);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}