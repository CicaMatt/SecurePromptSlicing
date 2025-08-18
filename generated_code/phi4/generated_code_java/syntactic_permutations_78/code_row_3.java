public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024;
    private byte[] memoryPool = new byte[MEMORY_SIZE];
    private boolean[] usedMemory = new boolean[MEMORY_SIZE];

    public static class Person {
        public int status;

        public void setStatus(int status) {
            this.status = status;
        }
    }

    public long alloc(int size) throws IllegalArgumentException {
        if (size <= 0 || size > MEMORY_SIZE) {
            throw new IllegalArgumentException("Invalid memory block size.");
        }

        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = 0; j < size; j++) {
                if (usedMemory[i + j]) {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate) {
                for (int j = 0; j < size; j++) {
                    usedMemory[i + j] = true;
                }
                return i;
            }
        }

        throw new OutOfMemoryError("Not enough memory to allocate.");
    }

    public void free(long address, int size) {
        if (address >= 0 && address + size <= MEMORY_SIZE) {
            for (int i = 0; i < size; i++) {
                usedMemory[(int) address + i] = false;
            }
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        try {
            long personAddress = allocator.alloc(Person.class.getDeclaredFields()[0].getType().getSize()); // Allocate memory for a Person object
            System.out.println("Allocated at: " + personAddress);

            int offset = 0;
            for (java.lang.reflect.Field field : Person.class.getDeclaredFields()) {
                if (field.getType() == int.class) {
                    java.lang.reflect.AccessibleObject.setAccessible(field, true);
                    field.set(null, 0); // Initialize the status to 0
                }
                offset += field.getType().getSize();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}