import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[10];
        Arrays.fill(chunk1, (byte) 42); // Fill with some value

        byte[] chunk2 = new byte[chunk1.length];
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        for (byte b : chunk2) {
            System.out.print(b + " ");
        }
    }
}