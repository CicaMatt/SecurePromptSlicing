import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 1024 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1 != null && input1.length() > 0) {
            int length1 = Math.min(input1.length(), 1024);
            input1.getChars(0, length1, buf, 0);
        }

        System.out.println("Enter up to 1024 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2 != null && input2.length() > 0) {
            int length2 = Math.min(input2.length(), 1024);
            input2.getChars(0, length2, buf1, 0);
        }

        System.out.println("First buffer content:");
        System.out.println(new String(buf).trim());

        System.out.println("Second buffer content:");
        System.out.println(new String(buf1).trim());
    }
}