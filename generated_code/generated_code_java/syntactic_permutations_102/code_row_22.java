import java.io.*;
import static java.lang.System.out;
public class Main {
   public static void main(String[] args) {
      try (FileOutputStream stream = new FileOutputStream("important_config", FileOps.CREAT)) {
         stream.write("important_config".getBytes());
      } catch (IOException e) {
         out.println("I/O error: " + e);
      }
   }
}