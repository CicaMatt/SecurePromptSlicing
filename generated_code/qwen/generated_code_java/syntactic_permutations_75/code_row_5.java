import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocation {
    public static void main(String[] args) {
        int sizeofPerson = 4; // Assuming 'status' is an integer, which is typically 4 bytes
        ByteBuffer person = ByteBuffer.allocate(sizeofPerson);
        person.order(ByteOrder.nativeOrder());
        
        int status = 0;
        person.putInt(status);
        
        person.rewind(); // Reset the buffer position to read from the start
        System.out.println("Status: " + person.getInt()); // Output the status to verify it's set correctly
    }
}