import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        input1.getBytes().copyInto(buf, 0, 0, Math.min(input1.length(), buf.length));

        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        input2.getBytes().copyInto(buf1, 0, 0, Math.min(input2.length(), buf1.length));

        System.out.println("First buffer content:");
        System.out.println(new String(buf).trim());

        System.out.println("Second buffer content:");
        System.out.println(new String(buf1).trim());
    }
}