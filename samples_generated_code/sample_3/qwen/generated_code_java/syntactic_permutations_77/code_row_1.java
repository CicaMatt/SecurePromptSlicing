import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class PersonAllocator {
    public static void main(String[] args) {
        int statusSize = Integer.BYTES; // Size of integer in bytes
        int nameCapacity = 10; // Assuming a fixed size for the name
        ByteBuffer buffer = ByteBuffer.allocate(statusSize + (nameCapacity * Character.BYTES));

        int status = 0;
        String name = "John";

        buffer.putInt(status);
        putString(buffer, name, nameCapacity);

        buffer.flip();

        int allocatedStatus = buffer.getInt();
        String allocatedName = getString(buffer, nameCapacity);

        System.out.println("Allocated Status: " + allocatedStatus);
        System.out.println("Allocated Name: " + allocatedName);
    }

    private static void putString(ByteBuffer buffer, String s, int capacity) {
        byte[] bytes = s.getBytes(StandardCharsets.UTF_8);
        if (bytes.length > capacity) {
            throw new IllegalArgumentException("String is too long for the given capacity");
        }
        buffer.put(bytes);
        for (int i = bytes.length; i < capacity; i++) {
            buffer.put((byte) 0); // Null padding
        }
    }

    private static String getString(ByteBuffer buffer, int capacity) {
        byte[] bytes = new byte[capacity];
        buffer.get(bytes);
        int length = 0;
        while (length < bytes.length && bytes[length] != 0) {
            length++;
        }
        return new String(bytes, 0, length, StandardCharsets.UTF_8);
    }
}