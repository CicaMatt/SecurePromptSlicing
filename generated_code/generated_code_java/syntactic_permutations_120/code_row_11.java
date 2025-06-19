import java.util.*;

public class ChunkCopier {
    public static void main(String[] args) {
        byte[] firstChunk = new byte[10];
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte)(Math.random() * 256);
        }

        byte[] secondChunk = Arrays.copyOf(firstChunk, firstChunk.length);
        System.out.println("Contents of second chunk: " + Arrays.toString(secondChunk));
    }
}