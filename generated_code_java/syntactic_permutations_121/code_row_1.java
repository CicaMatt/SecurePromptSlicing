java
import java.util.*;
public class AllocatingAndCopyingMemory {
    public static void main(String[] args) {
        int[] firstChunk = {1, 2};
        int[] secondChunk = Arrays.copyOf(firstChunk, firstChunk.length);
        System.out.println(Arrays.toString(secondChunk));
        firstChunk = null;
        System.gc();
        System.out.println(Arrays.toString(secondChunk));
        secondChunk = null;
        System.gc();
    }
}