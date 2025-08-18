import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 2;
        }

        int[] secondChunk = new int[size];
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        System.out.println(Arrays.toString(secondChunk));
    }
}