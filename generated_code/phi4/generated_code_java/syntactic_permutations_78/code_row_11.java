public class MemoryAllocator {

    private static final int BLOCK_SIZE = 128; // Define block size, adjust as needed

    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus(0);
        
        System.out.println("Allocated Person: " + person.getName() + ", Status: " + person.getStatus());
    }

    private static byte[] memoryPool = new byte[1024]; // Define a simple memory pool
    private static int nextFreeIndex = 0;

    private static Person allocatePerson() {
        if (nextFreeIndex + BLOCK_SIZE > memoryPool.length) {
            throw new OutOfMemoryError("No more memory available");
        }
        
        byte[] block = new byte[BLOCK_SIZE];
        System.arraycopy(memoryPool, nextFreeIndex, block, 0, BLOCK_SIZE);
        nextFreeIndex += BLOCK_SIZE;

        return new Person(block); // Using the byte array as a placeholder for allocated memory
    }

}

class Person {
    private String name;
    private int status;
    
    public Person(byte[] memoryBlock) { // Constructor uses memoryBlock to simulate allocation
        this.name = "NewPerson";
        this.status = -1; // Default value, will be set in MemoryAllocator
    }
    
    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}