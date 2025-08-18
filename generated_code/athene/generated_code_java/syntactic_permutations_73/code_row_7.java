import java.nio.ByteBuffer;

class Person {
    // Assuming some fields for Person class
    private String name;
    private int age;

    public static long sizeOf() {
        return 16; // Simplified assumption: 8 bytes for String reference and 4 bytes for int, plus padding
    }
}

public class MemoryAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(Person.sizeOf());
        System.out.println("Pointer to the allocated memory block: " + buffer);
    }
}