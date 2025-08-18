import java.util.Objects;

public class Person {
    String name;
    int age;

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Memory allocated for person: " + Objects.toString(person, "null"));
    }
}

class MemoryAllocator {
    public static <T> T allocateMemory(Class<T> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory", e);
        }
    }
}

class ExampleUsage {
    public static void main(String[] args) {
        Person person = MemoryAllocator.allocateMemory(Person.class);
        System.out.println("Memory allocated for person: " + Objects.toString(person, "null"));
    }
}