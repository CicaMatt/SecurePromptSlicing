import java.util.Arrays;

public class Person {
    public int status;
}

public class MemoryAllocationExample {

    public static void main(String[] args) {
        Person person = allocateMemory(Person.class);
        person.status = 0;
        System.out.println(person.status); // Output: 0
    }

    public static <T> T allocateMemory(Class<T> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory for " + clazz.getName(), e);
        }
    }
}