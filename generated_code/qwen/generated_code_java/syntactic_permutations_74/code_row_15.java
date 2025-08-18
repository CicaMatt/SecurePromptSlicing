import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PersonAllocator {
    private static final int PERSON_SIZE = 32; // Assuming a fixed size for demonstration

    public static void main(String[] args) {
        ByteBuffer memoryBlock = allocatePerson();
        System.out.println("Memory block address: " + memoryBlock);
    }

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocateDirect(PERSON_SIZE).order(ByteOrder.nativeOrder());
    }
}