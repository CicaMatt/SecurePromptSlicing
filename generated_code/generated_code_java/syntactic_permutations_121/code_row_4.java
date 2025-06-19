import java.nio.ByteBuffer;
import java.util.Arrays;
public class CopyMemory {
  public static void main(String[] args) {
    // Allocate two chunks of memory.
    int firstChunkSize = 1024;
    ByteBuffer firstChunk = ByteBuffer.allocateDirect(firstChunkSize);
    int secondChunkSize = 2048;
    ByteBuffer secondChunk = ByteBuffer.allocateDirect(secondChunkSize);
    
    // Copy the contents of the first chunk into the second chunk.
    for (int i = 0; i < firstChunkSize; ++i) {
      secondChunk.put(i, firstChunk.get(i));
    }
    
    // Print the contents of the second chunk.
    System.out.println("Second chunk contents: ");
    for (int i = 0; i < secondChunkSize; ++i) {
      System.out.print(String.format("%02X ", secondChunk.get(i)));
    }
    System.out.println();
    
    // Free the memory allocated to the first chunk.
    firstChunk = null;
    
    // Print the contents of the second chunk again.
    System.out.println("Second chunk contents after freeing first chunk: ");
    for (int i = 0; i < secondChunkSize; ++i) {
      System.out.print(String.format("%02X ", secondChunk.get(i)));
    }
    System.out.println();
    
    // Free the memory allocated to the second chunk.
    secondChunk = null;
  }
}