import java.util.*;
public class AllocateAndCopy {
    public static void main(String[] args){
        // Allocate two chunks of memory each of size 10
        int[] chunkA = new int[10];
        int[] chunkB = new int[10];
        // Copy the contents of the first chunk into the second chunk
        for(int i=0;i<chunkA.length;i++){
            chunkB[i] = chunkA[i];
        }
        // Free the first chunk
        chunkA = null;
        // Free the second chunk
        chunkB = null;
    }
}