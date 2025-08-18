import java.nio.ByteBuffer;

public class Main {
    public static void main(String[] args) {
        int sizeofPerson = 4; // Assuming 'status' is an integer which takes 4 bytes
        ByteBuffer memoryBlock = ByteBuffer.allocate(sizeofPerson);
        
        Person person = new Person(memoryBlock);
        person.setStatus(0);
    }
}

class Person {
    private ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(status);
    }

    public int getStatus() {
        return buffer.getInt(0);
    }
}