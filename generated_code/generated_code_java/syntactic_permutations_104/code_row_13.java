import java.io.*;
public class File {
    public static void main(String[] args) {
        String filename = "/etc/important-config";
        int fd = open(filename, O_RDWR | O_CREAT);
        if (fd == -1) {
            System.out.println("Error opening file");
            return;
        }
        String important_config = "This is a string of config data";
        write(fd, important_config.getBytes());
    }
}