import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(java.lang.reflect.Array.getByteLength(new Person()));
        Person person = new Person();
        setPersonStatus(buffer, person, 0);
        System.out.println("Person status: " + person.status);
    }

    private static void setPersonStatus(ByteBuffer buffer, Person person, int status) {
        person.status = status;
    }
}
