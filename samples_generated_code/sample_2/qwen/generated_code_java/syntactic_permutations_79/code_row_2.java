import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter up to 1024 characters:");

        String input = reader.readLine();
        if (input.length() > bufferSize) {
            input = input.substring(0, bufferSize);
        }

        for (int i = 0; i < input.length(); i++) {
            buf[i] = (byte) input.charAt(i);
            buf1[i] = (byte) input.charAt(i);
        }
    }
}