public class MemoryCopier {
    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] srcBuffer = message.getBytes();
        byte[] destBuffer = new byte[srcBuffer.length];

        copyMemory(destBuffer, srcBuffer, srcBuffer.length);

        System.out.println(new String(destBuffer));
    }
}