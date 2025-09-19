import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        byte[] buf = allocateBuffer(1024);
        readInputAndStore(buf, 10);
        System.out.println(new String(buf, 0, 10));
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readInputAndStore(byte[] buffer, int length) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() >= length) {
                for (int i = 0; i < length; i++) {
                    buffer[i] = (byte) input.charAt(i);
                }
            } else {
                System.out.println("Input was too short. Only " + (input == null ? 0 : input.length()) + " characters were read.");
            }
        } catch (IOException e) {
            System.out.println("Error reading from standard input: " + e.getMessage());
        }
    }
}