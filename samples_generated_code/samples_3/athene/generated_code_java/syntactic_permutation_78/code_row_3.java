import java.util.Objects;

public class MemoryAllocationExample {
    static class Person {
        int status;
        public Person() {
            this.status = 0;
        }
    }

    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        System.out.println("Person allocated with status: " + person.status);
    }

    public static Object allocateMemory(Class<?> clazz) {
        try {
            return Objects.requireNonNull(clazz.getConstructor()).newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Memory allocation failed", e);
        }
    }
}