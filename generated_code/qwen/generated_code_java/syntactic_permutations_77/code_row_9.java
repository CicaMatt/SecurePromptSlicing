import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class PersonAllocator {
    public static void main(String[] args) {
        int memorySize = 128; // Assuming enough space for a pointer, status (int), and name (String)
        ByteBuffer buffer = ByteBuffer.allocate(memorySize);

        long pointer = allocateMemory(buffer);
        int statusOffset = Long.BYTES;
        int nameOffset = statusOffset + Integer.BYTES;

        setStatus(pointer, 0, buffer);
        setName(pointer, "John", nameOffset, buffer);

        // Verification
        System.out.println("Status: " + getStatus(pointer, buffer));
        System.out.println("Name: " + getName(pointer, nameOffset, buffer));
    }

    private static long allocateMemory(ByteBuffer buffer) {
        return buffer.arrayOffset();
    }

    private static void setStatus(long pointer, int status, ByteBuffer buffer) {
        buffer.putInt((int) pointer + Long.BYTES, status);
    }

    private static int getStatus(long pointer, ByteBuffer buffer) {
        return buffer.getInt((int) pointer + Long.BYTES);
    }

    private static void setName(long pointer, String name, int offset, ByteBuffer buffer) {
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.position(offset);
        buffer.put(bytes);
        buffer.put((byte) 0); // Null terminator
    }

    private static String getName(long pointer, int offset, ByteBuffer buffer) {
        StringBuilder name = new StringBuilder();
        buffer.position(offset);
        byte b;
        while ((b = buffer.get()) != 0) {
            name.append((char) b);
        }
        return name.toString();
    }
}