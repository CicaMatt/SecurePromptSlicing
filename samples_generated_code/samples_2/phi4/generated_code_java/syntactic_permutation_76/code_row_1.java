public class MemoryManager {
    private static final int MEMORY_SIZE = 1024; // Size of the heap in bytes
    private byte[] memory;
    private boolean[] status;

    public MemoryManager() {
        memory = new byte[MEMORY_SIZE];
        status = new boolean[MEMORY_SIZE / sizeofPerson()];
    }

    private int sizeofPerson() {
        return 32; // Assuming person structure takes 32 bytes (adjust as necessary)
    }

    public int allocPerson() {
        for (int i = 0; i < memory.length - sizeofPerson(); i++) {
            boolean canAllocate = true;
            for (int j = 0; j < sizeofPerson(); j++) {
                if (status[i + j]) {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = 0; j < sizeofPerson(); j++) {
                    status[i + j] = true;
                }
                return i;
            }
        }
        throw new OutOfMemoryError("No memory available to allocate a person structure.");
    }

    public void freePerson(int address) {
        if (address < 0 || address >= memory.length - sizeofPerson()) {
            throw new IllegalArgumentException("Invalid address");
        }
        for (int i = 0; i < sizeofPerson(); i++) {
            status[address + i] = false;
        }
    }

    public static void main(String[] args) {
        MemoryManager manager = new MemoryManager();
        int address = manager.allocPerson();
        System.out.println("Allocated at: " + address);
        manager.freePerson(address);
        System.out.println("Freed memory at: " + address);
    }
}