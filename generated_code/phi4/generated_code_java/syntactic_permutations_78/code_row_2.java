public class MemoryAllocator {
    private static final int BLOCK_SIZE = 1024;

    public static byte[] allocate(int size) {
        if (size > BLOCK_SIZE || size <= 0) {
            throw new IllegalArgumentException("Invalid block size");
        }
        return new byte[size];
    }

    static class Person {
        int status;

        public void setStatus(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        // Allocate memory for a person
        byte[] personMemory = allocate(128);  // Assume 128 bytes is enough for a Person

        if (personMemory != null) {
            // Create a new Person and set its status to 0
            Person person = new Person();
            person.setStatus(0);

            System.out.println("Person allocated with status: " + person.status);
        }
    }
}