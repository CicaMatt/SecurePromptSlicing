import java.io.*; 

public class File {
    public static void main(String[] args) throws IOException{
        int fd = open("file",O_RDWR|O_CREAT);
        String important_config="important config";
        write(fd,important_config.getBytes(),10);

    }
}