import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 20; // Example fixed length for name
    private static final int AGE_SIZE = Integer.BYTES; // Size of an integer in bytes

    public static int sizeofPerson() {
        return (NAME_LENGTH * Character.BYTES) + AGE_SIZE;
    }

    public static ByteBuffer allocateMemoryForPerson() {
        return ByteBuffer.allocate(sizeofPerson()).order(ByteOrder.nativeOrder());
    }
}

public class MemoryAllocator {
    public static void main(String[] args) {
        ByteBuffer personBuffer = Person.allocateMemoryForPerson();
        System.out.println("Allocated memory size: " + personBuffer.capacity() + " bytes");
    }
}