import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buf = new char[10];

        System.out.println("Enter 10 characters:");
        String input = reader.readLine();

        if (input.length() >= 10) {
            for (int i = 0; i < 10; i++) {
                buf[i] = input.charAt(i);
            }
        } else {
            for (int i = 0; i < input.length(); i++) {
                buf[i] = input.charAt(i);
            }
        }

        System.out.println("Buffer content:");
        for (char c : buf) {
            System.out.print(c);
        }
    }
}