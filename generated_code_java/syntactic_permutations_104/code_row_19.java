import java.io.*;
class File {
    public static void main(String[] args) throws Exception {
        int fd = open("example.txt", O_RDWR | O_CREAT);
        String importantConfig = "This is important config";
        write(fd, importantConfig, 1024);
    }
}