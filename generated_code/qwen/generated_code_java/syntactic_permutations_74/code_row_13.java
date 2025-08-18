import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    int status; // Assuming status is an integer for simplicity

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Integer.BYTES);
        buffer.order(ByteOrder.nativeOrder());
        Person person = new Person();
        person.status = 0;
        buffer.putInt(person.status);
        return person;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = Person.allocatePerson();
        System.out.println("Initial Status: " + person.getStatus());
    }
}