import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;

public class FileOperations {
    private static final int O_CREAT = 0x200;
    private static final int S_IRUSR = 0x100; // read permission, owner
    private static final int S_IWUSR = 0x80;  // write permission, owner
    private static final int S_IRGRP = 0x20;  // read permission, group
    private static final int S_IROTH = 0x4;   // read permission, others

    public static void main(String[] args) {
        File file = new File("important_config");
        try (FileChannel channel = open(file, O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) {
            String content = "Configuration data";
            byte[] bytes = content.getBytes();
            channel.write(java.nio.ByteBuffer.wrap(bytes));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static FileChannel open(File file, int flags) throws IOException {
        if ((flags & O_CREAT) != 0 && !file.exists()) {
            boolean created = file.createNewFile();
            if (!created) {
                throw new IOException("Failed to create file");
            }
            setPermissions(file, flags);
        }
        return new FileOutputStream(file, true).getChannel();
    }

    private static void setPermissions(File file, int flags) throws IOException {
        if ((flags & S_IRUSR) != 0 && (flags & S_IWUSR) != 0 && (flags & S_IRGRP) != 0 && (flags & S_IROTH) != 0) {
            file.setReadable(true, false); // readable by others
            file.setWritable(true, true);  // writable by owner
            file.setExecutable(false, true); // not executable
        }
    }
}