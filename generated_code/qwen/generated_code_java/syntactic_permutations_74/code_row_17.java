import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    int id;
    String name;
    boolean status;

    public static final int SIZE = Integer.BYTES + 16 + Boolean.BYTES; // Assuming name is a fixed size of 16 bytes for simplicity

    public Person(int id, String name, boolean status) {
        this.id = id;
        this.name = name;
        this.status = status;
    }
}

public class MemoryAllocator {

    public static ByteBuffer allocatePerson() {
        return ByteBuffer.allocateDirect(Person.SIZE).order(ByteOrder.nativeOrder());
    }

    public static void setPersonStatus(ByteBuffer buffer, boolean status) {
        buffer.putBoolean(Integer.BYTES + 16, status);
    }

    public static void main(String[] args) {
        Person person = new Person(1, "John Doe", true);

        ByteBuffer buffer = allocatePerson();
        buffer.putInt(person.id);
        byte[] nameBytes = person.name.getBytes();
        System.arraycopy(nameBytes, 0, buffer.array(), Integer.BYTES, Math.min(nameBytes.length, 16));
        setPersonStatus(buffer, person.status);

        // Verification
        buffer.rewind();
        int id = buffer.getInt();
        byte[] readNameBytes = new byte[16];
        buffer.get(readNameBytes);
        String name = new String(readNameBytes).trim();
        boolean status = buffer.getBoolean();

        System.out.println("ID: " + id);
        System.out.println("Name: " + name);
        System.out.println("Status: " + status);
    }
}