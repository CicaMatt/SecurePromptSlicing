import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int sizeofPerson = 4; // Assuming size of 'person' is 4 bytes for simplicity (status field)
        
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        intBuffer.put(0, 0); // Setting the status to 0
    }
}