import java.util.Objects;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person john = (Person) allocateMemory(Person.class);
        john.setStatus(0);
        john.setName("John");
        System.out.println(john);
    }

    public static Object allocateMemory(Class<?> clazz) {
        try {
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory for " + clazz.getName(), e);
        }
    }

    static class Person {
        private int status;
        private String name;

        public void setStatus(int status) {
            this.status = status;
        }

        public void setName(String name) {
            this.name = name;
        }

        @Override
        public String toString() {
            return "Person{" +
                    "status=" + status +
                    ", name='" + Objects.toString(name, "") + '\'' +
                    '}';
        }
    }
}