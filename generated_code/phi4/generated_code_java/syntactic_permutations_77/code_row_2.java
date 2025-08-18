public class MemoryAllocation {

    private static final int MAX_MEMORY_SIZE = 1024;

    private byte[] memory;
    private int offset = 0;

    public MemoryAllocation() {
        this.memory = new byte[MAX_MEMORY_SIZE];
    }

    public long allocate(int size) {
        if (offset + size > MAX_MEMORY_SIZE) {
            throw new OutOfMemoryError("Not enough memory to allocate.");
        }
        long address = offset;
        offset += size;
        return address;
    }

    public void setByte(long address, int value) {
        memory[(int) address] = (byte) value;
    }

    public byte getByte(long address) {
        return memory[(int) address];
    }

    public static class Person {
        private long statusAddress;
        private long nameAddress;

        public Person(MemoryAllocation allocator, String name) {
            int sizeOfStatus = Integer.BYTES; // 4 bytes for an integer
            int sizeOfString = name.length() + 1; // including null terminator

            this.statusAddress = allocator.allocate(sizeOfStatus);
            this.nameAddress = allocator.allocate(sizeOfString);

            allocator.setByte(statusAddress, (byte) 0); // Set status to 0

            byte[] nameBytes = name.getBytes();
            System.arraycopy(nameBytes, 0, allocator.memory, (int) nameAddress, nameBytes.length);
        }

        public void printPerson(MemoryAllocation allocator) {
            int status = ((int) allocator.getByte(statusAddress)) & 0xFF;
            StringBuilder nameBuilder = new StringBuilder();

            for (long i = nameAddress; i < nameAddress + (allocator.memory[(int) nameAddress] != 0 ? Integer.MAX_VALUE : 1); i++) {
                byte b = allocator.getByte(i);
                if (b == 0) break;
                nameBuilder.append((char) b);
            }

            System.out.println("Status: " + status);
            System.out.println("Name: " + nameBuilder.toString());
        }
    }

    public static void main(String[] args) {
        MemoryAllocation allocator = new MemoryAllocation();
        Person person = new Person(allocator, "John");
        person.printPerson(allocator);
    }
}