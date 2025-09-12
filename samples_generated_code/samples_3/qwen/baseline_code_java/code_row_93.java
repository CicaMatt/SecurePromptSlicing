import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    static final int SIZE = Integer.BYTES; // Assuming 'status' is an integer

    private ByteBuffer buffer;

    public Person() {
        this.buffer = ByteBuffer.allocate(SIZE).order(ByteOrder.nativeOrder());
    }

    public void setStatus(int status) {
        this.buffer.putInt(0, status);
    }

    public int getStatus() {
        return this.buffer.getInt(0);
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        person.setStatus(0);
        
        System.out.println("Person status: " + person.getStatus());
    }
}