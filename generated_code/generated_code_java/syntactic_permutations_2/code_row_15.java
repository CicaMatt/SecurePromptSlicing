import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] destination = new byte[10];
        byte[] source = "Hello".getBytes();
        copyMemory(destination, source, 5);
        System.out.println(Arrays.toString(destination));
    }

    private static void copyMemory(byte[] destination, byte[] source, int numOfBytes) {
        for (int i = 0; i < numOfBytes; i++) {
            destination[i] = source[i];
        }
    }
}