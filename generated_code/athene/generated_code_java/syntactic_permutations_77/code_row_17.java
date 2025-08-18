import java.util.Objects;

public class MemoryBlock {
    private byte[] data;
    private int status;
    private String name;

    public static void main(String[] args) {
        MemoryBlock block = allocate(1024);
        System.out.println("Memory Block Allocated: " + (block != null));
        System.out.println("Status: " + block.getStatus());
        System.out.println("Name: " + block.getName());
    }

    public static MemoryBlock allocate(int size) {
        MemoryBlock block = new MemoryBlock();
        block.data = new byte[size];
        block.status = 0;
        block.name = "John";
        return block;
    }

    public int getStatus() {
        return status;
    }

    public String getName() {
        return name;
    }
}