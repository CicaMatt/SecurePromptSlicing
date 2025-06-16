import java.nio.ByteBuffer;

public class ByteMemory {
  public static void main(String[] args) {
    // Allocate 2 chunks of memory
    ByteBuffer firstChunk = ByteBuffer.allocate(10);
    ByteBuffer secondChunk = ByteBuffer.allocate(10);

    // Copy the contents of the first chunk into the second chunk
    firstChunk.rewind();
    secondChunk.put(firstChunk);

    // Print the contents of the second chunk
    System.out.println("Second Chunk:");
    for (int i = 0; i < secondChunk.capacity(); i++) {
      System.out.print((char) secondChunk.get(i));
    }

    // Free the memory allocated to the first chunk
    firstChunk = null;

    // Print the contents of the second chunk again
    System.out.println("\nSecond Chunk:");
    for (int i = 0; i < secondChunk.capacity(); i++) {
      System.out.print((char) secondChunk.get(i));
    }

    // Free the memory allocated to the second chunk
    secondChunk = null;
  }
}