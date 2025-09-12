import java.util.Arrays;

public class MemoryAllocation {

    private static final int MEMORY_SIZE = 1024;
    private byte[] memoryBlock;
    private boolean isAllocated;
    private String name;

    public MemoryAllocation() {
        this.memoryBlock = new byte[MEMORY_SIZE];
        this.isAllocated = false;
        this.name = "";
    }

    public void* allocate(int size) {
        if (size > MEMORY_SIZE || isAllocated) {
            return null;
        }
        memoryBlock = Arrays.copyOf(memoryBlock, size);
        isAllocated = true;
        return memoryBlock;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public static void main(String[] args) {
        MemoryAllocation ma = new MemoryAllocation();
        byte[] allocatedMemory = (byte[]) ma.allocate(100);
        
        if (allocatedMemory != null) {
            System.out.println("Memory allocated successfully.");
            ma.setName("John");
            System.out.println("Name set to: " + ma.getName());
        } else {
            System.out.println("Memory allocation failed.");
        }
    }
}


Note: Java does not support returning pointers directly as in C/C++. The above code simulates memory allocation by resizing a byte array.