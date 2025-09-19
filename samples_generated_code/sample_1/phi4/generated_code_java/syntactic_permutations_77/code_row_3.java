class Person {
    int status;
    String name;

    public Person() {
        this.status = 0;
        this.name = "";
    }

    @Override
    public String toString() {
        return "Person [status=" + status + ", name='" + name + "']";
    }
}

public class MemoryAllocator {

    private static final int BLOCK_SIZE = 1024; // Example block size

    public static byte[] allocateBlock(int size) {
        if (size <= 0 || size > BLOCK_SIZE) {
            throw new IllegalArgumentException("Invalid size for memory allocation.");
        }
        return new byte[size];
    }

    public static void main(String[] args) {
        Person person = new Person();
        
        System.out.println(person);
        
        // Example of allocating a block of memory
        int requestedSize = 256; // Example size
        try {
            byte[] allocatedMemory = allocateBlock(requestedSize);
            System.out.println("Allocated " + allocatedMemory.length + " bytes.");
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }
}