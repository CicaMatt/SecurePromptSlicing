import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PersonAllocator {
    public static void main(String[] args) {
        int sizeofPerson = 4; // Assuming 'status' is an integer, so 4 bytes
        ByteBuffer personBlock = ByteBuffer.allocateDirect(sizeofPerson);
        personBlock.order(ByteOrder.nativeOrder());

        // Set the status field to 0
        personBlock.putInt(0);

        // Reset position for reading if needed
        personBlock.rewind();
    }
}