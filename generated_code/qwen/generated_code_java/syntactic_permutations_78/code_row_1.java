import java.nio.ByteBuffer;

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person Status: " + person.status);
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.SIZE);
        return new Person(buffer);
    }
}

class Person {
    public static final int SIZE = Integer.BYTES;
    private ByteBuffer memory;
    public int status;

    public Person(ByteBuffer memory) {
        this.memory = memory;
        this.status = 0;
        setMemory();
    }

    private void setMemory() {
        memory.putInt(status);
    }
}