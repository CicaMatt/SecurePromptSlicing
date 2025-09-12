public class MemoryAllocationExample {

    private static final int MEMORY_SIZE = 1024;

    public static void main(String[] args) {
        int blockSize = 32; // Size of the Person object in bytes
        byte[] memory = new byte[MEMORY_SIZE];

        Person person = (Person) alloc(blockSize, memory);
        if (person != null) {
            person.setStatus(0);
            System.out.println("Person created with status: " + person.getStatus());
        }
    }

    public static Object alloc(int size, byte[] memory) {
        int offset = 0;

        for (int i = 0; i < memory.length - size + 1; i++) {
            if (isFreeBlock(i, size, memory)) {
                allocateBlock(i, size, memory);
                return new Person(memory, i, size);
            }
        }

        System.out.println("Not enough memory to allocate block of size: " + size);
        return null;
    }

    private static boolean isFreeBlock(int start, int size, byte[] memory) {
        for (int i = start; i < start + size; i++) {
            if (memory[i] != 0) {
                return false;
            }
        }
        return true;
    }

    private static void allocateBlock(int start, int size, byte[] memory) {
        for (int i = start; i < start + size; i++) {
            memory[i] = 1;
        }
    }

    static class Person {
        private final byte[] memory;
        private final int offset;
        private final int size;

        public Person(byte[] memory, int offset, int size) {
            this.memory = memory;
            this.offset = offset;
            this.size = size;
        }

        public void setStatus(int status) {
            // Assuming the first 4 bytes are used for storing an integer (status)
            byte[] statusBytes = intToByteArray(status);
            System.arraycopy(statusBytes, 0, memory, offset, statusBytes.length);
        }

        public int getStatus() {
            byte[] statusBytes = new byte[4];
            System.arraycopy(memory, offset, statusBytes, 0, 4);
            return byteArrayToInt(statusBytes);
        }

        private static byte[] intToByteArray(int value) {
            return new byte[]{
                (byte) (value >>> 24),
                (byte) (value >>> 16),
                (byte) (value >>> 8),
                (byte) value
            };
        }

        private static int byteArrayToInt(byte[] bytes) {
            int value = 0;
            for (int i = 0; i < 4; i++) {
                value |= ((bytes[i] & 0xFF) << (24 - i * 8));
            }
            return value;
        }
    }
}