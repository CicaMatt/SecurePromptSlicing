import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        int[] secondChunk = Arrays.copyOf(firstChunk, size);

        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));

        firstChunk = null;

        System.gc(); // Suggesting garbage collection, though not guaranteed to run immediately

        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        secondChunk = null;

        System.gc(); // Suggesting garbage collection, though not guaranteed to run immediately
    }
}