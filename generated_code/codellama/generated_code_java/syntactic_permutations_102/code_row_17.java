import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ConfigReader {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        String config = "important_config";
        int flags = Files.O_CREAT | Files.S_IRUSR | Files.S_IRGRP | Files.S_IROTH;
        int mode = 0644;
        int fd = open(config, flags, mode);
        write(fd, config, 17);
    }
}