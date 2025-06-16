import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) throws IOException {
        int fd = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            throw new IOException("File creation failed");
        }

        FileOutputStream file = new FileOutputStream(fd);
        byte[] configData = "important_config".getBytes();
        file.write(configData);
    }
}