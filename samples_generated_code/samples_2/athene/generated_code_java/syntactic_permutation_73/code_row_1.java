import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        System.out.println(person);
    }

    public static Object allocateMemory(Class<?> clazz) {
        int size = getSizeOf(clazz);
        ByteBuffer buffer = ByteBuffer.allocate(size);
        return newObject(buffer, clazz);
    }

    private static int getSizeOf(Class<?> clazz) {
        if (clazz == Person.class) {
            // Assuming Person has a few fields, this is just an example.
            // In real code, you would calculate the actual size based on the fields.
            return 24; // Example size
        }
        throw new IllegalArgumentException("Unsupported class");
    }

    private static Object newObject(ByteBuffer buffer, Class<?> clazz) {
        try {
            return clazz.getConstructor(ByteBuffer.class).newInstance(buffer);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static class Person {
        private String name;
        private int age;

        public Person(ByteBuffer buffer) {
            // Example constructor that uses the buffer to initialize fields
            this.name = buffer.asCharBuffer().toString();
            this.age = buffer.getInt();
        }

        @Override
        public String toString() {
            return "Person{name='" + name + "', age=" + age + "}";
        }
    }
}