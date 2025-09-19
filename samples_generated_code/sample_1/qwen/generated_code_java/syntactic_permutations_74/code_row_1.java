import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(12); // Assuming a simple struct with 3 integers (id, age, status)
        IntBuffer intBuffer = buffer.asIntBuffer();

        Person person = new Person(intBuffer);
        person.setStatus(0);

        return person;
    }
}

class Person {
    private final IntBuffer buffer;

    public Person(IntBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.put(2, status); // Assuming the third integer in the struct is for the status
    }

    public int getStatus() {
        return buffer.get(2);
    }
}