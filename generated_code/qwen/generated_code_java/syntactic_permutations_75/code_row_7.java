import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(java.lang.reflect.Array.getByteLength(new Person()));
        Person person = new Person();
        person.status = 0;
        System.out.println("Person status: " + person.status);
    }
}