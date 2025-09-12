public class MemoryAllocator {
    private static final int STATUS_INDEX = 0;
    private static final int NAME_START_INDEX = Integer.BYTES;

    public static void main(String[] args) {
        int size = Integer.BYTES + "John".length() + 1; // Size for status (int) and name (String with null terminator)
        byte[] memoryBlock = allocateMemory(size);

        setStatus(memoryBlock, 0);
        setName(memoryBlock, "John");

        System.out.println("Status: " + getStatus(memoryBlock));
        System.out.println("Name: " + getName(memoryBlock));
    }

    public static byte[] allocateMemory(int size) {
        return new byte[size];
    }

    public static void setStatus(byte[] memoryBlock, int status) {
        for (int i = 0; i < Integer.BYTES; i++) {
            memoryBlock[i] = (byte) ((status >> (i * 8)) & 0xFF);
        }
    }

    public static int getStatus(byte[] memoryBlock) {
        return (memoryBlock[STATUS_INDEX] & 0xFF) |
               ((memoryBlock[STATUS_INDEX + 1] & 0xFF) << 8) |
               ((memoryBlock[STATUS_INDEX + 2] & 0xFF) << 16) |
               ((memoryBlock[STATUS_INDEX + 3] & 0xFF) << 24);
    }

    public static void setName(byte[] memoryBlock, String name) {
        byte[] bytes = name.getBytes();
        System.arraycopy(bytes, 0, memoryBlock, NAME_START_INDEX, bytes.length);
        memoryBlock[NAME_START_INDEX + bytes.length] = 0; // Null terminator
    }

    public static String getName(byte[] memoryBlock) {
        StringBuilder name = new StringBuilder();
        for (int i = NAME_START_INDEX; ; i++) {
            if (memoryBlock[i] == 0) { // Null terminator found
                break;
            }
            name.append((char) memoryBlock[i]);
        }
        return name.toString();
    }
}