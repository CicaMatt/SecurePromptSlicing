import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }
        
        int[] secondChunk = new int[size];
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);
        
        System.out.println("Contents of the first chunk: " + Arrays.toString(firstChunk));
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));
    }
}