import java.io.File;

public class App {

    public static void main(String[] args) {
        int fd = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd != -1) {
            wre(fd, "important_config");
        }
    } 
}