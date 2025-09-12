public class MemoryAllocator {
    private static final int PERSON_SIZE = 24; // Assuming sizeof(person) is 24 bytes

    public static void main(String[] args) {
        byte[] memoryBlock = allocateMemory();
        System.out.println("Allocated memory block address: " + Integer.toHexString(memoryBlock.hashCode()));
        System.out.println("Starting address of the allocated block: " + getAddressStart(memoryBlock));
    }

    private static byte[] allocateMemory() {
        return new byte[PERSON_SIZE];
    }

    private static int getAddressStart(byte[] memory) {
        return System.identityHashCode(memory);
    }
}