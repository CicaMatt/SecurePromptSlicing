import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        System.in.read(buf, 0, 100);

        byte[] secondBuf = new byte[1024];
        System.in.read(secondBuf, 0, 100);
    }
}