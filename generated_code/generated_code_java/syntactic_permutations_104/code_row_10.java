import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException{
        File f = new File("important_config");
        int fd = open(f.getPath(), O_RDWR | O_CREAT);
        if (fd == -1){
            throw new RuntimeException("Failed to create file " + f.getName());
        }
        try{
            write(fd, "important config", 0, 17);
        }finally{
            close(fd);
        }
    }
}