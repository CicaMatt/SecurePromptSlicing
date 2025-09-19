import java.nio.ByteBuffer;

class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocationExample {

    private static final int SIZE_OF_PERSON = Integer.BYTES; // Assuming sizeof(person) is equivalent to the size of an integer

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(SIZE_OF_PERSON);
        
        // Allocate memory and set status
        Person person = new Person();
        int offset = 0;
        buffer.putInt(offset, person.status);

        System.out.println("Status: " + buffer.getInt(offset));
    }
}