import java.io.*;
class AllocateAndCopy {
    public static void main(String[] args) throws Exception {
        // Declare variables
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[10];
        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);
        // Free the first chunk
        firstChunk = null;
        // Free the second chunk
        secondChunk = null;
    }
}