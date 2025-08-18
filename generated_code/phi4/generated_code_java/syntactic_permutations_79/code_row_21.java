import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        input1.getChars(0, Math.min(input1.length(), 100), buf, 0);

        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        input2.getChars(0, Math.min(input2.length(), 100), buf1, 0);

        System.out.println("Enter up to 1024 characters for additional storage:");
        String input3 = reader.readLine();
        if (input3.length() > 1024) {
            input3 = input3.substring(0, 1024);
        }
        input3.getChars(0, Math.min(input3.length(), 1024), buf1, 100);

        System.out.println("First buffer content:");
        System.out.println(new String(buf, 0, input1.length()));

        System.out.println("Second buffer content (combined):");
        System.out.println(new String(buf1, 0, input2.length() + Math.min(input3.length(), 1024)));
    }
}