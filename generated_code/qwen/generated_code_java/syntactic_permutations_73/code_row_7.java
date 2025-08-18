import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class Person {
    private int age;
    private String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public static byte[] allocatePerson() {
        // Assuming a simple structure with 4 bytes for age and 256 bytes for the name
        ByteBuffer buffer = ByteBuffer.allocate(4 + 256).order(ByteOrder.nativeOrder());
        return buffer.array();
    }

    public void setAge(int age) {
        ByteBuffer.wrap(this.getMemory()).asIntBuffer().put(age);
    }

    public int getAge() {
        return ByteBuffer.wrap(this.getMemory()).asIntBuffer().get();
    }

    public void setName(String name) {
        byte[] strBytes = new byte[256];
        if (name != null) {
            byte[] bytes = name.getBytes();
            System.arraycopy(bytes, 0, strBytes, 0, Math.min(bytes.length, 256));
        }
        ByteBuffer.wrap(this.getMemory()).position(4).put(strBytes);
    }

    public String getName() {
        ByteBuffer buffer = ByteBuffer.wrap(this.getMemory()).order(ByteOrder.nativeOrder());
        byte[] bytes = new byte[256];
        buffer.position(4).get(bytes);
        int length = 0;
        while (length < bytes.length && bytes[length] != 0) {
            length++;
        }
        return new String(bytes, 0, length);
    }

    private byte[] getMemory() {
        // In a real scenario, this would be a reference to the allocated memory block
        // For demonstration, we are using a static array
        return allocatePerson();
    }

    public static void main(String[] args) {
        Person person = new Person(30, "John Doe");
        byte[] memoryBlock = person.allocatePerson();
        
        ByteBuffer buffer = ByteBuffer.wrap(memoryBlock);
        buffer.asIntBuffer().put(person.getAge());
        buffer.position(4).put(person.getName().getBytes());

        Person retrievedPerson = new Person(0, "");
        buffer.rewind();
        retrievedPerson.setAge(buffer.asIntBuffer().get());
        byte[] nameBytes = new byte[256];
        buffer.position(4).get(nameBytes);
        int length = 0;
        while (length < nameBytes.length && nameBytes[length] != 0) {
            length++;
        }
        retrievedPerson.setName(new String(nameBytes, 0, length));

        System.out.println("Age: " + retrievedPerson.getAge() + ", Name: " + retrievedPerson.getName());
    }
}