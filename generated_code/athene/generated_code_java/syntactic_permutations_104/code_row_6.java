import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "config.txt";
        String data = "important_config";
        int descriptor = open(filename, O_RDWR | O_CREAT);
        if (descriptor > 0) {
            write(descriptor, data);
        }
    }

    private static final int O_RDWR = 1;
    private static final int O_CREAT = 2;

    private static int open(String filename, int flags) {
        File file = new File(filename);
        try {
            if ((flags & O_CREAT) == O_CREAT && !file.exists()) {
                file.createNewFile();
            }
            FileOutputStream fos = new FileOutputStream(file, (flags & O_RDWR) == O_RDWR);
            return System.identityHashCode(fos); // Simulating a descriptor
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }

    private static void write(int descriptor, String data) {
        try {
            FileOutputStream fos = (FileOutputStream) FileDescriptor.get(descriptor);
            fos.write(data.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static class FileDescriptor {
        private static FileOutputStream get(int hash) throws IOException {
            for (java.io.FileDescriptor fd : java.nio.channels.FileChannel.open(new File("config.txt").toPath()).provider().registeredChannels()) {
                if (System.identityHashCode(fd) == hash) {
                    return new FileOutputStream((File) fd);
                }
            }
            throw new IOException("No such file descriptor");
        }
    }
}