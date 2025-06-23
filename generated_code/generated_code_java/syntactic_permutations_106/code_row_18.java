import java.io.FileOutputStream;
import java.io.IOException;

public class SuperSecretInfo {
  public static void main(String[] args) {
    // Create a string with some super secret info.
    String superSecret = "This is top-secret information.";

    try {
      // Create a file and write the super secret info to it.
      FileOutputStream outFile = new FileOutputStream("super_secret.txt");
      outFile.write(superSecret.getBytes());
      outFile.close();

      // Change the permissions of to read-only for the owner.
      ProcessBuilder builder = new ProcessBuilder("chmod", "400", "super_secret.txt");
      builder.start().waitFor();

    } catch (IOException e) {
      System.err.println(e);
    }

    // Print the name of to the screen.
    System.out.println("super_secret.txt");
  }
}