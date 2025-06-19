import java.io.*;  

public class HelloWorld {

     public static void main(String[] args) throws Exception {
         int fd;
        String filename = "important_config";  // File name  
        fd = open(filename, O_CREAT | S_IRUSR | S_IWUSR | S_IROTH);   // Creating a file with read and write permissions
        write(fd, "important_config"); // Write content to the file
     }
}