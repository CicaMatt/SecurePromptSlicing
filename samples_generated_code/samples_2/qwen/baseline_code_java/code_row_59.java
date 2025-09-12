import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 2;
        }

        int[] secondChunk = Arrays.copyOf(firstChunk, firstChunk.length);

        System.out.println(Arrays.toString(secondChunk));
    }
}