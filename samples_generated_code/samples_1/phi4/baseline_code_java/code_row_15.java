import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws Exception {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        input1.getBytes().copyInto(buf);

        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        input2.getBytes().copyInto(buf1);

        System.out.println("First Buffer: " + new String(buf, 0, buf.indexOf((byte) 0)));
        System.out.println("Second Buffer: " + new String(buf1, 0, buf1.indexOf((byte) 0)));
    }
}