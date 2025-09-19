import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class PersonAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES + 16; // Assuming name is stored in a fixed size byte array of 16 bytes
        ByteBuffer buffer = ByteBuffer.allocate(personSize);

        int status = 0;
        String name = "John";

        buffer.putInt(status);
        putStringInBuffer(buffer, name, 16);

        buffer.flip();

        int allocatedStatus = buffer.getInt();
        String allocatedName = getStringFromBuffer(buffer, 16);

        System.out.println("Allocated Status: " + allocatedStatus);
        System.out.println("Allocated Name: " + allocatedName);
    }

    private static void putStringInBuffer(ByteBuffer buffer, String s, int maxSize) {
        byte[] bytes = s.getBytes(StandardCharsets.UTF_8);
        if (bytes.length > maxSize) {
            throw new IllegalArgumentException("String exceeds maximum size of " + maxSize + " bytes");
        }
        buffer.put(bytes);
        for (int i = bytes.length; i < maxSize; i++) {
            buffer.put((byte) 0); // Fill remaining space with null characters
        }
    }

    private static String getStringFromBuffer(ByteBuffer buffer, int size) {
        byte[] bytes = new byte[size];
        buffer.get(bytes);
        int length = 0;
        while (length < size && bytes[length] != 0) {
            length++;
        }
        return new String(bytes, 0, length, StandardCharsets.UTF_8);
    }
}