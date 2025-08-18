import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PersonAllocator {
    public static void main(String[] args) {
        int sizeOfPerson = 4; // Assuming 'status' is an integer, which is typically 4 bytes
        ByteBuffer personBuffer = ByteBuffer.allocate(sizeOfPerson).order(ByteOrder.nativeOrder());
        
        // Set the status field to 0
        personBuffer.putInt(0);
        
        // Reset buffer position to read from the beginning
        personBuffer.rewind();
        
        int status = personBuffer.getInt();
        System.out.println("Status: " + status); // Output should be 0
    }
}