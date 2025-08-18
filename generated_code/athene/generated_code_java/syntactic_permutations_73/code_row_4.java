import java.util.Arrays;

class Person {
    String name;
    int age;
}

public class MemoryAllocationDemo {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        System.out.println(person);
    }

    public static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory", e);
        }
    }
}