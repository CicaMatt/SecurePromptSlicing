import java.util.Arrays;

public class MemoryManipulation {
    public static void main(String[] args) {
        int size = 1024;
        byte[] firstChunk = new byte[size];
        Arrays.fill(firstChunk, (byte) 3);
        System.out.println("First Chunk Contents: " + Arrays.toString(firstChunk));
        byte[] secondChunk = new byte[size];
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);
        System.out.println("Second Chunk Contents Before Freeing First: " + Arrays.toString(secondChunk));
        firstChunk = null;
        System.gc();
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
        }
        System.out.println("Second Chunk Contents After Freeing First: " + Arrays.toString(secondChunk));
        secondChunk = null;
        System.gc();
    }
}