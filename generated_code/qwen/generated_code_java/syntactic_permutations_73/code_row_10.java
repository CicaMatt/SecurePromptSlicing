import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private static final int SIZE_OF_INT = 4; // Assuming int is 4 bytes
    private static final int NAME_LENGTH = 20; // Assuming name is a string of max 20 characters
    private static final int SIZE_OF_PERSON = SIZE_OF_INT + (NAME_LENGTH * Character.BYTES);

    private ByteBuffer buffer;

    public Person() {
        this.buffer = ByteBuffer.allocate(SIZE_OF_PERSON).order(ByteOrder.nativeOrder());
    }

    public void setAge(int age) {
        buffer.putInt(age);
    }

    public int getAge() {
        return buffer.getInt(0);
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes();
        if (bytes.length > NAME_LENGTH) {
            throw new IllegalArgumentException("Name is too long");
        }
        buffer.position(SIZE_OF_INT);
        buffer.put(bytes);
        buffer.position(SIZE_OF_PERSON); // Reset position after writing name
    }

    public String getName() {
        byte[] bytes = new byte[NAME_LENGTH];
        buffer.position(SIZE_OF_INT);
        buffer.get(bytes);
        int i = 0;
        while (i < NAME_LENGTH && bytes[i] != 0) {
            i++;
        }
        return new String(bytes, 0, i);
    }

    public static void main(String[] args) {
        Person person = new Person();
        person.setAge(30);
        person.setName("John Doe");
        System.out.println("Age: " + person.getAge());
        System.out.println("Name: " + person.getName());
    }
}