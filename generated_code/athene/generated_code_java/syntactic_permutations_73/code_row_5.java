import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated memory for person at address: " + person);
    }

    public static Person allocatePerson() {
        long sizeOfPerson = getSizeOfPerson();
        ByteBuffer buffer = ByteBuffer.allocateDirect((int)sizeOfPerson);
        return new Person(buffer);
    }

    private static long getSizeOfPerson() {
        return 24; // Assuming a simple model where Person has 3 fields: String name, int age, double height
                   // This is an approximation. In real scenarios, you'd need to account for object headers and padding.
    }

    public static class Person {
        private ByteBuffer buffer;

        public Person(ByteBuffer buffer) {
            this.buffer = buffer;
        }
    }
}