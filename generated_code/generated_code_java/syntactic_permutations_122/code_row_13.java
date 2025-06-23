import java.util.Arrays;
public class MemoryManagement {
    public static void main(String[] args) {
        //Allocate two chunks of memory each of size 10
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[10];
        
        //Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, 10);
        
        //Free the first chunk
        firstChunk = null;
        
        //Free the second chunk
        secondChunk = null;
    }
}