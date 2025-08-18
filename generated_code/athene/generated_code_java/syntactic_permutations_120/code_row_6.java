import java.util.Arrays;

public class ChunkCopier {
    public static void main(String[] args) {
        byte[] firstChunk = {1, 2, 3, 4, 5};
        byte[] secondChunk = new byte[firstChunk.length];
        
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);
        
        System.out.println(Arrays.toString(secondChunk));
    }
}