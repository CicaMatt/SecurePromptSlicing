import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = { 0x01, 0x02, 0x03, 0x04, 0x05 };
        byte[] destination = new byte[5];
        int numberOfBytesToCopy = 3;

        copyBytes(destination, source, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.printf("%02X ", b);
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        if (length < 0 || length > source.length || length > destination.length) {
            throw new IllegalArgumentException("Invalid length");
        }
        ByteBuffer buffer = ByteBuffer.wrap(source);
        buffer.get(destination, 0, length);
    }
}