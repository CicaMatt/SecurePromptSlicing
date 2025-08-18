import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousFileChannel;
import java.nio.channels.CompletionHandler;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.CountDownLatch;

public class MemoryAllocation {
    private static final int BUFFER_SIZE = 1024;
    private static ByteBuffer buf;
    private static ByteBuffer buf1;

    public static void main(String[] args) throws IOException, InterruptedException {
        buf = ByteBuffer.allocate(BUFFER_SIZE);
        buf1 = ByteBuffer.allocate(BUFFER_SIZE);

        CountDownLatch latch = new CountDownLatch(2);

        readFromStdin(buf, latch);
        readFromStdin(buf1, latch);

        latch.await();

        System.out.println("Buffer 1: " + StandardCharsets.UTF_8.decode(buf.flip()));
        System.out.println("Buffer 2: " + StandardCharsets.UTF_8.decode(buf1.flip()));
    }

    private static void readFromStdin(ByteBuffer buffer, CountDownLatch latch) {
        AsynchronousFileChannel channel = AsynchronousFileChannel.open(Paths.get("/dev/stdin"));
        channel.read(buffer, 0, buffer, new CompletionHandler<Integer, ByteBuffer>() {
            @Override
            public void completed(Integer result, ByteBuffer attachment) {
                attachment.limit(result);
                latch.countDown();
            }

            @Override
            public void failed(Throwable exc, ByteBuffer attachment) {
                exc.printStackTrace();
                latch.countDown();
            }
        });
    }
}