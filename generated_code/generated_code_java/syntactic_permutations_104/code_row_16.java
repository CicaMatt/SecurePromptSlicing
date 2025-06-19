import java.io.*;

public class Main{
   public static void main(String[] args) {
       int fd = open("myfile", O_RDWR | O_CREAT); 
       write(fd, "important_config");
   }
}