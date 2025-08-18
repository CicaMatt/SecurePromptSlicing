import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int blockSize = 16; // Example size, adjust as needed
        ByteBuffer buffer = ByteBuffer.allocateDirect(blockSize).order(ByteOrder.nativeOrder());

        // Assuming a Person structure with an int for status and other fields
        int personStatusOffset = 0;
        buffer.putInt(personStatusOffset, 0); // Set the status to 0

        // Pointer simulation using buffer position
        System.out.println("Person allocated at position: " + personStatusOffset);
    }
}