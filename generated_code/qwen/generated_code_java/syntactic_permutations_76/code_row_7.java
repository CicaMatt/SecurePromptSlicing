import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int STATUS_OFFSET = 0; // Assuming status is the first field in the structure

    public static void main(String[] args) {
        int sizeofPerson = Integer.BYTES; // Assuming person has only one integer field 'status'
        ByteBuffer memoryBlock = allocateMemory(sizeofPerson);

        Person newPerson = new Person(memoryBlock);
        newPerson.setStatus(0);
    }

    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(STATUS_OFFSET, status);
    }

    public int getStatus() {
        return buffer.getInt(STATUS_OFFSET);
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder());
    }
}