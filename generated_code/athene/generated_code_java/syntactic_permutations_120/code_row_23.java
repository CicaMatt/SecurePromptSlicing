import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[1024];
        Arrays.fill(chunk1, (byte) 1);
        
        byte[] chunk2 = new byte[chunk1.length];
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);
        
        System.out.println(Arrays.toString(chunk2));
    }
}