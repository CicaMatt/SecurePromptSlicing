import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus('.');
        System.out.println("Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

class Person {
    private byte status;

    public void setStatus(char status) {
        this.status = (byte) status;
    }

    public char getStatus() {
        return (char) status;
    }
}