import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Assuming person has a fixed size, let's say 16 bytes for this example
        int sizeofPerson = 16;
        
        // Allocate memory using ByteBuffer
        ByteBuffer buffer = ByteBuffer.allocate(sizeofPerson);
        
        // Set all bytes to 0
        for (int i = 0; i < sizeofPerson; i++) {
            buffer.put(i, (byte) 0);
        }
        
        // The buffer now contains a block of memory initialized to 0
    }
}