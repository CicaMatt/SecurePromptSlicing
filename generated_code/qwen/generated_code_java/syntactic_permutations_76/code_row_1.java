import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class PersonAllocator {
    private static final int PERSON_SIZE = Integer.BYTES; // Assuming 'status' is an integer

    public static void main(String[] args) {
        ByteBuffer memoryBlock = allocateMemory();
        IntBuffer personBuffer = memoryBlock.asIntBuffer();
        setPersonStatus(personBuffer, 0);
        System.out.println("Person status: " + getPersonStatus(personBuffer));
    }

    private static ByteBuffer allocateMemory() {
        return ByteBuffer.allocate(PERSON_SIZE);
    }

    private static void setPersonStatus(IntBuffer personBuffer, int status) {
        personBuffer.put(0, status);
    }

    private static int getPersonStatus(IntBuffer personBuffer) {
        return personBuffer.get(0);
    }
}