public class MemoryAllocator {
    private static final int MAX_MEMORY_SIZE = 1024; // Example max size for simplicity
    private byte[] memory;
    private boolean[] allocated;

    public MemoryAllocator() {
        this.memory = new byte[MAX_MEMORY_SIZE];
        this.allocated = new boolean[MAX_MEMORY_SIZE];
    }

    public int allocate(int size) {
        if (size <= 0 || size > MAX_MEMORY_SIZE) return -1;
        
        for (int i = 0; i <= MAX_MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = i; j < i + size; j++) {
                if (allocated[j]) {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate) {
                for (int j = i; j < i + size; j++) {
                    allocated[j] = true;
                }
                return i;
            }
        }
        
        return -1;
    }

    public void free(int start, int size) {
        for (int i = start; i < start + size && i < MAX_MEMORY_SIZE; i++) {
            allocated[i] = false;
        }
    }

    public byte[] getMemoryBlock(int start, int size) {
        if (start < 0 || start >= MAX_MEMORY_SIZE || size <= 0 || start + size > MAX_MEMORY_SIZE) {
            return null;
        }
        byte[] block = new byte[size];
        System.arraycopy(memory, start, block, 0, size);
        return block;
    }

    public void setMemoryBlock(int start, int size, byte[] data) {
        if (start < 0 || start >= MAX_MEMORY_SIZE || size <= 0 || start + size > MAX_MEMORY_SIZE || data.length != size) {
            return;
        }
        System.arraycopy(data, 0, memory, start, size);
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        int blockSize = 128; // Example block size
        int pointer = allocator.allocate(blockSize);
        if (pointer != -1) {
            Person person = new Person();
            person.setStatus(0);
            person.setName("John");
            
            byte[] personData = serializePerson(person);
            allocator.setMemoryBlock(pointer, personData.length, personData);

            // Example of how to retrieve the data
            byte[] retrievedData = allocator.getMemoryBlock(pointer, personData.length);
            Person retrievedPerson = deserializePerson(retrievedData);
            System.out.println("Retrieved Person: " + retrievedPerson.getName() + ", Status: " + retrievedPerson.getStatus());

            // Free memory after use
            allocator.free(pointer, blockSize);
        }
    }

    private static byte[] serializePerson(Person person) {
        try (ByteArrayOutputStream bos = new ByteArrayOutputStream();
             DataOutputStream dos = new DataOutputStream(bos)) {

            dos.writeInt(person.getStatus());
            dos.writeUTF(person.getName());
            return bos.toByteArray();

        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    private static Person deserializePerson(byte[] data) {
        try (ByteArrayInputStream bis = new ByteArrayInputStream(data);
             DataInputStream dis = new DataInputStream(bis)) {

            int status = dis.readInt();
            String name = dis.readUTF();
            return new Person(status, name);

        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    static class Person {
        private int status;
        private String name;

        public Person() {}

        public Person(int status, String name) {
            this.status = status;
            this.name = name;
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }
}