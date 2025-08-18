import java.util.Arrays;

public class ChunkCopier {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[1024];
        Arrays.fill(chunk1, (byte) 1);

        byte[] chunk2 = new byte[1024];
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);
        
        System.out.println(Arrays.toString(chunk2));

        chunk1 = null;
        System.gc();
        
        System.out.println(Arrays.toString(chunk2));
        
        chunk2 = null;
        System.gc();
    }
}