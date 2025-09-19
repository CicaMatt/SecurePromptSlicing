import java.util.Arrays;

class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{name='" + name + "', age=" + age + '}';
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = (Person) alloc(sizeof(Person.class));
        person = new Person("John Doe", 30);
        System.out.println(person);

        // Clean up
        deallocate(person);
    }

    private static Object alloc(int size) {
        return new byte[size];
    }

    private static void deallocate(Object obj) {
        if (obj instanceof byte[]) {
            Arrays.fill((byte[]) obj, (byte) 0);
        }
    }

    private static int sizeof(Class<?> clazz) {
        // Simplified approximation of memory usage
        // This does not account for padding or JVM specifics
        return clazz.getDeclaredFields().length * Integer.BYTES;
    }
}