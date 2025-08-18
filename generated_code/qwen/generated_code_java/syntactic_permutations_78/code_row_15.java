import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Integer.BYTES);
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0); // Set status to 0
        return new Person(buffer);
    }
}

class Person {
    private final ByteBuffer memory;

    public Person(ByteBuffer memory) {
        this.memory = memory;
    }

    public int getStatus() {
        return memory.getInt(0);
    }
}