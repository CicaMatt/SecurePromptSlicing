import java.nio.ByteBuffer;

class Person {
    String name;
    int age;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        long sizeOfPerson = (long) (8 + 4); // Assuming String uses 8 bytes and int uses 4 bytes for simplicity
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeOfPerson);
        System.out.println(buffer.address());
    }
}