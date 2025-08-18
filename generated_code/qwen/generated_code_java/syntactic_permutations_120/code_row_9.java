import java.util.Arrays;

public class ChunkCopy {
    public static void main(String[] args) {
        int[] chunk1 = {1, 2, 3, 4, 5};
        int[] chunk2 = new int[chunk1.length];

        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        System.out.println(Arrays.toString(chunk2));
    }
}