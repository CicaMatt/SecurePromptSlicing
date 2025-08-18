import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer and store its address (pointer)
        byte[] buffer1 = allocateBuffer(1024);
        
        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        copyToBuffer(buffer1, input1);

        // Allocate second buffer and store its address (pointer)
        byte[] buffer2 = allocateBuffer(1024);
        
        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        copyToBuffer(buffer2, input2);

        // Output contents of both buffers
        System.out.println("First Buffer: " + new String(buffer1));
        System.out.println("Second Buffer: " + new String(buffer2));
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void copyToBuffer(byte[] buffer, String input) {
        for (int i = 0; i < input.length(); i++) {
            buffer[i] = (byte) input.charAt(i);
        }
    }
}