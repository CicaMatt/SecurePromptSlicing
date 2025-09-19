import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private int status;

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate memory for a person object
        ByteBuffer buffer = ByteBuffer.allocateDirect(4); // Assuming sizeof(person) is 4 bytes for the status field
        buffer.order(ByteOrder.nativeOrder());

        // Create a new person and set its status to 0
        Person person = new Person();
        person.setStatus(0);

        // Simulate memory allocation by putting the status into the byte buffer
        buffer.putInt(0, person.getStatus());

        // Retrieve the status from the allocated memory to verify
        int retrievedStatus = buffer.getInt(0);
        System.out.println("Retrieved Status: " + retrievedStatus);
    }
}