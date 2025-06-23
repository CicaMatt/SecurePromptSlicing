java
import java.util.*;
class MemoryChunks {
    public static void main(String[] args) {
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[firstChunk.length];
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte) i;
            secondChunk[i] = firstChunk[i];
        }
        System.out.println(Arrays.toString(secondChunk));
        firstChunk = null;
        System.gc();
        System.out.println(Arrays.toString(secondChunk));
        secondChunk = null;
    }
}