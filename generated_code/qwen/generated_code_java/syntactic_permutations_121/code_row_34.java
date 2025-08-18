import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        firstChunk = null;

        System.gc(); // Suggesting JVM to garbage collect

        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        secondChunk = null;

        System.gc(); // Suggesting JVM to garbage collect
    }
}