import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status);
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(4); // Assuming status is an int and occupies 4 bytes
        IntBuffer intBuffer = buffer.asIntBuffer();
        intBuffer.put(0); // Set status to 0

        return new Person(buffer, intBuffer);
    }
}

class Person {
    ByteBuffer byteBuffer;
    IntBuffer intBuffer;
    int status;

    public Person(ByteBuffer byteBuffer, IntBuffer intBuffer) {
        this.byteBuffer = byteBuffer;
        this.intBuffer = intBuffer;
        this.status = intBuffer.get(0);
    }
}