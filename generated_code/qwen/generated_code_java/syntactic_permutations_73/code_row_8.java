import java.nio.ByteBuffer;

class Person {
    private int age;
    private String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public static int sizeofPerson() {
        // Approximate size calculation for a Person object in Java
        // 4 bytes for 'age' (int)
        // 8 bytes for the reference to 'name'
        // Additional memory may be used by the JVM and garbage collector
        return Integer.BYTES + Long.BYTES;
    }

    public static ByteBuffer allocateMemoryForPerson() {
        int size = sizeofPerson();
        return ByteBuffer.allocate(size);
    }

    public static void main(String[] args) {
        ByteBuffer buffer = allocateMemoryForPerson();
        System.out.println("Allocated memory block starting at address: " + buffer);
    }
}