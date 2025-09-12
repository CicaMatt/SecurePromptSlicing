import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int SIZE_OF_PERSON = 16; // Assuming size of person is 16 bytes for this example

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocate(SIZE_OF_PERSON).order(ByteOrder.nativeOrder());
    }

    public static void setStatus(ByteBuffer person, byte status) {
        person.put(0, status); // Assuming the first byte is used for status
    }

    public static void main(String[] args) {
        ByteBuffer person = allocatePerson();
        byte status = 1; // Example status value
        setStatus(person, status);
        System.out.println("Status set to: " + person.get(0));
    }
}