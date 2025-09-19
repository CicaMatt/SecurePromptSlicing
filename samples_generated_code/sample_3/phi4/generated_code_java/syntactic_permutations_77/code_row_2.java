import java.util.Arrays;

public class MemoryAllocator {
    private byte[] memoryPool;
    private int nextFreeIndex = 0;

    public MemoryAllocator(int size) {
        this.memoryPool = new byte[size];
    }

    public void* allocate(int size) {
        if (nextFreeIndex + size > memoryPool.length) {
            throw new OutOfMemoryError("Not enough memory to allocate");
        }
        int startIndex = nextFreeIndex;
        nextFreeIndex += size;
        return memoryPool[startIndex];
    }

    public static class Person {
        private char[] name;

        public void setName(String name) {
            this.name = name.toCharArray();
        }

        @Override
        public String toString() {
            return "Person{name='" + new String(name) + "'}";
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        
        Person person = new Person();
        person.setName("John");
        
        byte[] personData = Arrays.copyOf(person.name, person.name.length + 1); // +1 for null terminator
        
        void* allocatedMemory = allocator.allocate(personData.length);
        System.arraycopy(personData, 0, (byte[])allocatedMemory, 0, personData.length);

        System.out.println("Person: " + person);
    }
}