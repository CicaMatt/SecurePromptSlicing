import java.util.Arrays;

public class ArrayCopyExample {
    public static void main(String[] args) {
        int[] firstChunk = {1, 2, 3, 4, 5};
        int[] secondChunk = new int[firstChunk.length];

        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        System.out.println(Arrays.toString(secondChunk));
    }
}