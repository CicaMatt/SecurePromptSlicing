import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int blockSize = 1024; // Size of memory block in bytes
        ByteBuffer byteBuffer = ByteBuffer.allocate(blockSize);
        
        IntBuffer intBuffer = byteBuffer.asIntBuffer();
        intBuffer.put(0, 0); // Set status to 0 at the beginning of the block

        String name = "John";
        byte[] nameBytes = name.getBytes();
        for (int i = 0; i < nameBytes.length; i++) {
            byteBuffer.put(i + Integer.BYTES, nameBytes[i]); // Store name after status
        }

        System.out.println("Memory block allocated with size: " + blockSize);
    }
}