import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        int bytesRead = System.in.read(buf);
        if (bytesRead > 0) {
            baos.write(buf, 0, Math.min(bytesRead, 100));
        }

        bytesRead = System.in.read(buf1);
        if (bytesRead > 0) {
            baos.write(buf1, 0, Math.min(bytesRead, 100));
        }

        String result = baos.toString(StandardCharsets.UTF_8.name());
        System.out.println(result);
    }
}