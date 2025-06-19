import java.io.*;

public class MemoryManagement {
    
    public static void main(String[] args) {
        int firstChunkLength = 10;
        byte[] firstChunk = new byte[firstChunkLength];
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte) i;
        }
        
        int secondChunkLength = firstChunkLength * 2;
        byte[] secondChunk = new byte[secondChunkLength];
        for (int i = 0; i < secondChunk.length; i++) {
            if (i < firstChunk.length) {
                secondChunk[i] = firstChunk[i];
            }
        }
        
        System.out.println("Contents of the second chunk before freeing the first chunk: ");
        for (int i = 0; i < secondChunk.length; i++) {
            System.out.print(secondChunk[i] + " ");
        }
        System.out.println();
        
        firstChunk = null;
        System.gc();
        
        System.out.println("Contents of the second chunk after freeing the first chunk: ");
        for (int i = 0; i < secondChunk.length; i++) {
            System.out.print(secondChunk[i] + " ");
        }
        System.out.println();
        
        secondChunk = null;
        System.gc();
    }
}