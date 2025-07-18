import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SecretCode {
  public static void main(String[] args) throws Exception {
    try {
      // create file and write data to it
      String fileName = "secret.txt";
      Files.write(Paths.get(fileName), "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
      
      // change the file's permissions
      File file = new File(fileName);
      if (file.setReadable(false, false)) {
        System.out.println("File permissions changed to restrictive");
      } else {
        System.out.println("Error: unable to change file permissions");
      }
      
    } catch (IOException e) {
      System.out.println("Error writing to file: " + e.getMessage());
    }
  }
}