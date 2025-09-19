public class MemoryManager {
    private byte[] memory;
    private int nextFreeIndex;

    public MemoryManager(int size) {
        memory = new byte[size];
        nextFreeIndex = 0;
    }

    public long allocate(int size) {
        if (nextFreeIndex + size > memory.length) {
            throw new RuntimeException("Out of memory");
        }
        long address = nextFreeIndex;
        nextFreeIndex += size;
        return address;
    }

    public void deallocate(long address, int size) {
        // Simple example: does not actually free memory
    }

    public void writeInt(int value, long address) {
        for (int i = 0; i < Integer.BYTES; i++) {
            memory[(int) address + i] = (byte) (value >> (i * 8));
        }
    }

    public int readInt(long address) {
        int value = 0;
        for (int i = 0; i < Integer.BYTES; i++) {
            value |= ((memory[(int) address + i] & 0xFF) << (i * 8));
        }
        return value;
    }

    public void writeString(String value, long address) {
        byte[] bytes = value.getBytes();
        for (int i = 0; i < bytes.length && (address + i) < memory.length; i++) {
            memory[(int) address + i] = bytes[i];
        }
    }

    public String readString(long address, int length) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length && (address + i) < memory.length; i++) {
            if (memory[(int) address + i] == 0) break;
            sb.append((char) memory[(int) address + i]);
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        MemoryManager manager = new MemoryManager(1024);

        long personAddress = manager.allocate(8); // Assuming Person is represented by 2 integers
        manager.writeInt(0, personAddress);       // Status
        manager.writeInt(personAddress + Integer.BYTES, 1); // Address of name

        long nameAddress = manager.allocate(5);   // "John" + null terminator
        manager.writeString("John", nameAddress);

        int status = manager.readInt(personAddress);
        System.out.println("Status: " + status);

        String name = manager.readString(manager.readInt(personAddress) + Integer.BYTES, 4);
        System.out.println("Name: " + name);
    }
}