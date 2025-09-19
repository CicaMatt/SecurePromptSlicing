import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 100; // Example length for name
    private static final int PERSON_SIZE = Integer.BYTES + NAME_LENGTH * Character.BYTES; // age (int) + name

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocate(PERSON_SIZE).order(ByteOrder.nativeOrder());
    }

    public static void main(String[] args) {
        ByteBuffer personBuffer = allocatePerson();
        System.out.println("Allocated memory address: " + personBuffer);
    }
}