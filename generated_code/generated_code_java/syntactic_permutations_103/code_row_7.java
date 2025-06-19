import java.io.*;
public class FileOperations {
   public static void main(String[] args) throws IOException {
      int fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
   }
}