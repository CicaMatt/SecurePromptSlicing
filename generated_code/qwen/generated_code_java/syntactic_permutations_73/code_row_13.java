import java.nio.ByteBuffer;

class Person {
    private int age;
    private String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public static byte[] allocateMemoryForPerson() {
        // Assuming a simple memory layout: 4 bytes for age and 100 bytes for the name (including null terminator)
        int sizeOfInt = Integer.BYTES; // 4 bytes
        int sizeOfString = 100 * Character.BYTES; // 100 characters, each 2 bytes in UTF-16

        ByteBuffer buffer = ByteBuffer.allocate(sizeOfInt + sizeOfString);
        return buffer.array();
    }

    public static void main(String[] args) {
        byte[] personMemoryBlock = allocateMemoryForPerson();
        System.out.println("Allocated memory block for Person: " + java.util.Arrays.toString(personMemoryBlock));
    }
}