import java.lang.reflect.Field;

public class MemoryAllocation {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        System.out.println(person);
    }

    public static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory for " + clazz.getName(), e);
        }
    }

    public static class Person {
        private String name;
        private int age;

        public Person() {}

        @Override
        public String toString() {
            return "Person{" +
                    "name='" + name + '\'' +
                    ", age=" + age +
                    '}';
        }
    }
}