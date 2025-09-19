import java.nio.ByteBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming 'person' only contains an integer 'status'
        ByteBuffer memoryBlock = ByteBuffer.allocate(sizeofPerson);
        
        Person person = new Person(memoryBlock);
        person.setStatus(0);
    }
}

class Person {
    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(0, status);
    }

    public int getStatus() {
        return buffer.getInt(0);
    }
}