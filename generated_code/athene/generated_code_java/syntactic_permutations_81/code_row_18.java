import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] memory = allocateMemory(1024);
        readAndStoreInput(memory, 10);
        System.out.println(new String(memory).trim());
    }

    private static byte[] allocateMemory(int size) {
        return new byte[size];
    }

    private static void readAndStoreInput(byte[] buffer, int length) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() > 0) {
                for (int i = 0; i < Math.min(length, input.length()); i++) {
                    buffer[i] = (byte) input.charAt(i);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}