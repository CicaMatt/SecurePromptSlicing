import java.io.*;

class FileCreation {
  public static void main(String[] args) throws Exception {
    try (FileOutputStream fos = new FileOutputStream("test", true);) {
      // Create a new file if it does not exist, or append to the existing one
    } catch (IOException ioe) {
      System.out.println("I/O Error: " + ioe.getMessage());
    }
  }
}