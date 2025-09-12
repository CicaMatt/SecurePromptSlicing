import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = 32; // Assuming each person occupies 32 bytes of memory

        // Allocate memory for a new person
        ByteBuffer personMemory = allocateMemory(personSize);

        // Example usage: Storing data in the allocated memory
        String name = "JohnDoe";
        int age = 30;
        storeStringInMemory(personMemory, 0, name);
        storeIntInMemory(personMemory, 16, age);

        // Retrieve and print stored data
        System.out.println("Name: " + retrieveStringFromMemory(personMemory, 0));
        System.out.println("Age: " + retrieveIntFromMemory(personMemory, 16));
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder());
    }

    private static void storeStringInMemory(ByteBuffer buffer, int offset, String value) {
        byte[] bytes = value.getBytes();
        for (int i = 0; i < bytes.length && i < 16; i++) { // Assuming name is stored in the first 16 bytes
            buffer.put(offset + i, bytes[i]);
        }
    }

    private static String retrieveStringFromMemory(ByteBuffer buffer, int offset) {
        byte[] bytes = new byte[16]; // Assuming name is stored in the first 16 bytes
        for (int i = 0; i < 16; i++) {
            byte b = buffer.get(offset + i);
            if (b == 0) break; // Stop at null terminator if present
            bytes[i] = b;
        }
        return new String(bytes, 0, firstNullIndex(bytes));
    }

    private static void storeIntInMemory(ByteBuffer buffer, int offset, int value) {
        buffer.putInt(offset, value);
    }

    private static int retrieveIntFromMemory(ByteBuffer buffer, int offset) {
        return buffer.getInt(offset);
    }

    private static int firstNullIndex(byte[] bytes) {
        for (int i = 0; i < bytes.length; i++) {
            if (bytes[i] == 0) return i;
        }
        return bytes.length;
    }
}