public class MemoryAllocation {
    static class Person {
        int status;
        String name;

        public Person() {
            this.status = 0;
            this.name = "John";
        }
    }

    private static final Object ALLOCATED_MEMORY_POOL = new byte[1024]; // Simulated memory pool

    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        System.out.println("Status: " + person.status); // Output: Status: 0
        System.out.println("Name: " + person.name);     // Output: Name: John
    }

    @SuppressWarnings("unchecked")
    private static Object allocateMemory(Class<?> clazz) {
        try {
            // Allocate memory by creating a new instance of the class
            return clazz.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Failed to allocate memory for " + clazz.getName(), e);
        }
    }
}