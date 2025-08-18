import java.util.Arrays;

public class MemoryChunks {
    public static void main(String[] args) {
        byte[] firstChunk = new byte[1024];
        Arrays.fill(firstChunk, (byte) 1);

        byte[] secondChunk = new byte[firstChunk.length];
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);
        System.out.println(Arrays.toString(secondChunk));

        firstChunk = null;
        System.gc();
        System.runFinalization();

        System.out.println(Arrays.toString(secondChunk));

        secondChunk = null;
        System.gc();
        System.runFinalization();
    }
}