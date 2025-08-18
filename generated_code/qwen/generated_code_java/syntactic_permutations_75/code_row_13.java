import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocator {
    private static final int SIZE_OF_PERSON = 32; // Example size, adjust as necessary

    public static void main(String[] args) {
        ByteBuffer personBlock = allocatePerson();
        personBlock.putInt(0, 0); // Set status to 0
    }

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocateDirect(SIZE_OF_PERSON).order(ByteOrder.nativeOrder());
    }
}