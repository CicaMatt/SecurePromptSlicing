public class MemoryAllocator {

    private byte[] memory;
    private int position;

    public MemoryAllocator(int totalSize) {
        this.memory = new byte[totalSize];
        this.position = 0;
    }

    @SuppressWarnings("unchecked")
    public <T> T allocate(Class<T> clazz, int size) {
        if (position + size > memory.length) {
            throw new OutOfMemoryError("Not enough memory to allocate " + size + " bytes");
        }
        T obj = clazz.cast(java.lang.reflect.Array.newInstance(clazz, 1)[0]);
        System.arraycopy(memory, position, java.nio.ByteBuffer.wrap(obj.getClass().isArray() ? (byte[]) obj : ByteBuffer.allocateDirect(size).array()), 0, size);
        position += size;
        return obj;
    }

    public static class Person {
        int status;

        public void setStatus(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);

        // Allocate memory for a Person object
        Person person = allocator.allocate(Person.class, 8);
        person.setStatus(0);

        System.out.println("Person status: " + person.status);
    }
}