public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Example memory size

    public static void main(String[] args) {
        byte[] memory = new byte[MEMORY_SIZE];

        Person person = (Person) allocate(memory, Person.class);
        person.setName("John");

        System.out.println(person.getName());
    }

    @SuppressWarnings("unchecked")
    private static Object allocate(byte[] memory, Class<?> clazz) {
        if (memory == null || clazz == null) {
            throw new IllegalArgumentException("Memory and class must not be null");
        }
        
        try {
            return clazz.newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            throw new RuntimeException("Failed to create instance of " + clazz.getName(), e);
        }
    }

    static class Person {
        private String name;

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }
}