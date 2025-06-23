import java.nio.file.*;
import java.io.*;
public class FileOpener {
  public static void main(String[] args) throws IOException {
    Path path = Paths.get("path/to/new/file");
    try (FileOutputStream fos = new FileOutputStream(path.toString())) {
      // Use the file output stream...
    } catch (FileNotFoundException e) {
      System.out.println("Error: " + e);
    }
  }
}