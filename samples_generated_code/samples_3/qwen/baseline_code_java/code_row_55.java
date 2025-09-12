import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class PersonAllocator {
    private static final int SIZE_OF_PERSON = 4; // Assuming 'status' is an integer

    public static void main(String[] args) {
        ByteBuffer personBlock = allocateMemory(SIZE_OF_PERSON);
        setStatus(personBlock, 0);
        
        // To verify the status is set to 0
        System.out.println("Status: " + getStatus(personBlock));
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder());
    }

    private static void setStatus(ByteBuffer person, int status) {
        person.putInt(0, status);
    }

    private static int getStatus(ByteBuffer person) {
        return person.getInt(0);
    }
}