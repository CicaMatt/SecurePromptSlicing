import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        byte[] buf1 = new byte[bufferSize];
        byte[] buf2 = new byte[bufferSize];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter first 100 characters:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        for (int i = 0; i < input1.length(); i++) {
            buf1[i] = (byte) input1.charAt(i);
        }

        System.out.println("Enter second 100 characters:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        for (int i = 0; i < input2.length(); i++) {
            buf2[i] = (byte) input2.charAt(i);
        }

        reader.close();
    }
}