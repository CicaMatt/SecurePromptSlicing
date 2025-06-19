import java.io.*;
    
    public class File {
      public static void main(String[] args) {
        int fd;
        byte[] config = "important_config".getBytes();
    
        try {
          fd = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
          write(fd, config, 0, config.length);
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
    }