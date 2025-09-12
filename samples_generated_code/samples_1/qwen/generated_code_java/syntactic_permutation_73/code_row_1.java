import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 100;
    private static final int TOTAL_SIZE = Integer.BYTES * 3 + NAME_LENGTH;

    private int age;
    private int height;
    private int weight;
    private byte[] name; // Fixed size for simplicity

    public Person() {
        this.name = new byte[NAME_LENGTH];
    }

    public static ByteBuffer allocateMemoryForPerson() {
        return ByteBuffer.allocate(TOTAL_SIZE).order(ByteOrder.nativeOrder());
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        ByteBuffer personBuffer = Person.allocateMemoryForPerson();
        System.out.println("Allocated memory address: " + personBuffer);
    }
}