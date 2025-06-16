import java.lang.*;
public class ImportantConfig {
    public static void main(String[] args) throws Exception {
        int fd = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        write(fd, "important_config");
    }
}