import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int NAME_LENGTH = 100; // Example length for name
    public static final int SIZEOF_PERSON = NAME_LENGTH * Character.BYTES + Integer.BYTES;

    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public ByteBuffer allocateMemory() {
        ByteBuffer buffer = ByteBuffer.allocate(SIZEOF_PERSON);
        buffer.order(ByteOrder.nativeOrder());
        byte[] nameBytes = new byte[NAME_LENGTH];
        if (name != null) {
            System.arraycopy(name.getBytes(), 0, nameBytes, 0, Math.min(name.length(), NAME_LENGTH));
        }
        buffer.put(nameBytes);
        buffer.putInt(age);
        buffer.rewind();
        return buffer;
    }

    public static void main(String[] args) {
        Person person = new Person("John Doe", 30);
        ByteBuffer memoryBlock = person.allocateMemory();
        byte[] nameBytes = new byte[NAME_LENGTH];
        memoryBlock.get(nameBytes);
        String name = new String(nameBytes).trim();
        int age = memoryBlock.getInt();
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }
}