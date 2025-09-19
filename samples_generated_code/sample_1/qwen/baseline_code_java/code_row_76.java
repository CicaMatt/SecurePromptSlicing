import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'status' is an integer
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeofPerson);
        IntBuffer intBuffer = buffer.asIntBuffer();
        
        int status = 0;
        intBuffer.put(status);
        
        System.out.println("Status: " + intBuffer.get(0));
    }
}