public class MemoryAllocator {

    private static final int PERSON_SIZE = Integer.BYTES * 2 + Character.BYTES; // Assuming Person has two integers (id, age) and one character (status)

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person ID: " + person.getId() + ", Age: " + person.getAge() + ", Status: " + person.getStatus());
    }

    private static Person allocatePerson() {
        // Allocate memory for a new Person
        byte[] memoryBlock = new byte[PERSON_SIZE];
        
        // Set the status to 0 (assuming it's stored as an ASCII character)
        memoryBlock[Integer.BYTES * 2] = 0; // Status at offset PERSON_SIZE - Character.BYTES

        return new Person(memoryBlock);
    }

    static class Person {
        private int id;
        private int age;
        private char status;

        public Person(byte[] memoryBlock) {
            if (memoryBlock.length != PERSON_SIZE) {
                throw new IllegalArgumentException("Invalid memory block size");
            }
            
            // Extract fields from the byte array
            this.id = byteArrayToInt(memoryBlock, 0);
            this.age = byteArrayToInt(memoryBlock, Integer.BYTES);
            this.status = (char) memoryBlock[Integer.BYTES * 2];
        }

        private int byteArrayToInt(byte[] bytes, int offset) {
            return ((bytes[offset] & 0xFF) << 24)
                | ((bytes[offset + 1] & 0xFF) << 16)
                | ((bytes[offset + 2] & 0xFF) << 8)
                | (bytes[offset + 3] & 0xFF);
        }

        public int getId() {
            return id;
        }

        public int getAge() {
            return age;
        }

        public char getStatus() {
            return status;
        }
    }
}