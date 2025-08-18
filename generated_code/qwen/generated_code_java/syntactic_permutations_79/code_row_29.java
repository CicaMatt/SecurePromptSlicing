import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        byte[] buffer1 = allocateAndCopy(1024);
        byte[] buffer2 = allocateAndCopy(1024);

        System.out.println("Buffer 1: " + new String(buffer1, StandardCharsets.UTF_8).trim());
        System.out.println("Buffer 2: " + new String(buffer2, StandardCharsets.UTF_8).trim());
    }

    private static byte[] allocateAndCopy(int size) throws IOException {
        byte[] buffer = new byte[size];
        ByteArrayOutputStream baos = new ByteArrayOutputStream(size);

        int bytesRead = System.in.read(buffer);
        if (bytesRead > 0) {
            baos.write(buffer, 0, Math.min(bytesRead, 100));
        }

        return baos.toByteArray();
    }
}