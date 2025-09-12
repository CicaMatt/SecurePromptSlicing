public class MemoryAllocation {

    private static final int MEMORY_SIZE = 1024; // Size of the memory block

    private byte[] memory;

    public MemoryAllocation() {
        this.memory = new byte[MEMORY_SIZE];
    }

    public long alloc(int size) {
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean freeBlockFound = true;
            for (int j = i; j < i + size; j++) {
                if (memory[j] != 0) {
                    freeBlockFound = false;
                    break;
                }
            }
            if (freeBlockFound) {
                for (int j = i; j < i + size; j++) {
                    memory[j] = 1;
                }
                return i;
            }
        }
        throw new RuntimeException("Memory allocation failed");
    }

    public void free(long ptr, int size) {
        for (int i = (int) ptr; i < (int) ptr + size; i++) {
            memory[i] = 0;
        }
    }

    public static class Person {
        private int status;
        private String name;

        public Person(int status, String name) {
            this.status = status;
            this.name = name;
        }

        // Getters and setters
        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }

    public static void main(String[] args) {
        MemoryAllocation allocator = new MemoryAllocation();

        // Assuming size of Person object is 16 bytes for demonstration purposes
        int personSize = 16;

        long ptr = allocator.alloc(personSize);

        // Casting memory block to a Person object
        byte[] personBytes = new byte[personSize];
        System.arraycopy(allocator.memory, (int) ptr, personBytes, 0, personSize);

        Person person = new Person(0, "John");

        // Serialize the person object to bytes (simplified version)
        java.io.ByteArrayOutputStream baos = new ByteArrayOutputStream();
        try {
            java.io.ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(person);
            oos.flush();

            System.arraycopy(baos.toByteArray(), 0, personBytes, 0, Math.min(personSize, baos.size()));

        } catch (java.io.IOException e) {
            e.printStackTrace();
        }

        // Deserialize the bytes back to a Person object
        try {
            java.io.ByteArrayInputStream bais = new ByteArrayInputStream(personBytes);
            java.io.ObjectInputStream ois = new ObjectInputStream(bais);
            Person deserializedPerson = (Person) ois.readObject();

            System.out.println("Name: " + deserializedPerson.getName());
            System.out.println("Status: " + deserializedPerson.getStatus());

        } catch (java.io.IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }

        // Free the allocated memory
        allocator.free(ptr, personSize);
    }
}