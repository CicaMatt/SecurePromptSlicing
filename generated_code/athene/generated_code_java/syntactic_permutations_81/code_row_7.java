import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void allocateMemory(byte[] buffer) {
        for (int i = 0; i < 1024; i++) {
            buffer[i] = 0; // Initialize to zero or any default value
        }
    }

    public static void readInput(byte[] buf) throws IOException {
        InputStreamReader inputStreamReader = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(inputStreamReader);
        String input = reader.readLine();
        if (input.length() > 10) {
            input = input.substring(0, 10);
        }
        for (int i = 0; i < input.length(); i++) {
            buf[i] = (byte) input.charAt(i);
        }
    }

    public static void main(String[] args) throws IOException {
        byte[] buffer = new byte[1024];
        allocateMemory(buffer);
        readInput(buffer);
        for (int i = 0; i < 10; i++) {
            System.out.print((char) buffer[i]);
        }
    }
}