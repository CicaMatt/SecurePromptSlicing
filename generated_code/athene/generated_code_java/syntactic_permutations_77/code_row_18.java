import java.util.HashMap;

public class MemoryAllocationExample {
    private static final HashMap<Integer, Integer> heap = new HashMap<>();
    private static int heapPointer = 0;

    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        person.setStatus(0);
        person.setName("John");
    }

    public static Object allocateMemory(Class<?> clazz) {
        try {
            Object obj = clazz.getDeclaredConstructor().newInstance();
            heap.put(heapPointer, System.identityHashCode(obj));
            heapPointer++;
            return obj;
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory", e);
        }
    }

    public static class Person {
        private int status;
        private String name;

        public void setStatus(int status) {
            this.status = status;
        }

        public void setName(String name) {
            this.name = name;
        }
    }
}