import java.nio.ByteBuffer;

public class PersonAllocator {
    public static void main(String[] args) {
        ByteBuffer person = allocatePerson();
        int statusOffset = 0; // Assuming status is the first field in the person struct
        person.putInt(statusOffset, 0);
    }

    private static ByteBuffer allocatePerson() {
        final int PERSON_SIZE = 16; // Example size of a person struct in bytes
        return ByteBuffer.allocate(PERSON_SIZE);
    }
}