public class MemoryCopy {
    public static void main(String[] args) throws Exception {
        int size = 10;
        byte[] data = new byte[size];
        for (int i = 0; i < size; i++) {
            data[i] = (byte) i;
        }
        ByteBuffer buffer = ByteBuffer.allocate(size);
        buffer.put(data);
        buffer.rewind();
        while (buffer.hasRemaining()) {
            System.out.println(buffer.get());
        }
    }
}