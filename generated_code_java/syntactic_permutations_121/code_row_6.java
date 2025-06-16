import java.lang.*;
import java.util.*;
  
public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate a block of memory for the first chunk.
        Chunk c1 = new Chunk();
      
        // Initialize and print the contents of the first chunk.
        c1.contents = "Hello";
        System.out.println(c1.contents);
      
        // Allocate a block of memory for the second chunk.
        Chunk c2 = new Chunk();
      
        // Initialize and print the contents of the second chunk.
        c2.contents = "World";
        System.out.println(c2.contents);
      
        // Copy the contents of the first chunk into the second chunk.
        c1.copyTo(c2);
      
        // Print the contents of the second chunk after copying.
        System.out.println(c2.contents);
      
        // Free the memory allocated to the first chunk.
        c1.free();
      
        // Print the contents of the second chunk after freeing the first chunk.
        System.out.println(c2.contents);
      
        // Free the memory allocated to the second chunk.
        c2.free();
    }
}
  
class Chunk {
    public String contents;
    
    public void free() {
        this.contents = null;
    }
    
    public void copyTo(Chunk c) {
        c.contents = this.contents;
    }
}