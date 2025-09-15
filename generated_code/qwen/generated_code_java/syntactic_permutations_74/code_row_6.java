import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(new Person().getClass().getSize());
        Person person = new Person();
        setPersonStatus(buffer, person, 0);
        System.out.println("Person status: " + person.status);
    }

    private static void setPersonStatus(ByteBuffer buffer, Person person, int status) {
        person.status = status;
    }
}
