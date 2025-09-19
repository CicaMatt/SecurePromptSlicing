import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PersonAllocator {
    public static void main(String[] args) {
        int sizeofPerson = 4; // Assuming 'status' is an integer, which is typically 4 bytes
        ByteBuffer personBlock = ByteBuffer.allocateDirect(sizeofPerson);
        personBlock.order(ByteOrder.nativeOrder());

        int statusFieldOffset = 0;
        personBlock.putInt(statusFieldOffset, 0);

        System.out.println("Person allocated with status: " + personBlock.getInt(statusFieldOffset));
    }
}