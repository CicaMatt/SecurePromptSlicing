import java.lang.reflect.Field;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        System.out.println(person);
    }

    public static Object allocateMemory(Class<?> clazz) {
        try {
            Field sizeField = Class.forName("java.lang.Runtime").getDeclaredField("sizeof");
            sizeField.setAccessible(true);
            int size = (int) sizeField.get(clazz);

            Object block = java.util.Arrays.newInstance(clazz, 1);
            return java.lang.reflect.Array.get(block, 0);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static class Person {
        String name;
        int age;

        @Override
        public String toString() {
            return "Person{name='" + name + "', age=" + age + '}';
        }
    }
}
