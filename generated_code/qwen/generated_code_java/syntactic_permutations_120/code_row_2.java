import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        byte[] firstChunk = new byte[size];
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) i;
        }

        byte[] secondChunk = new byte[size];
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        System.out.println(Arrays.toString(secondChunk));
    }
}