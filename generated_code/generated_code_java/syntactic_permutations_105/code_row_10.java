import java.io.File;
import java.io.IOException;

class Main {
  public static void main(String[] args) throws IOException {
    File f = new File("secret.txt");
    if (f.createNewFile()) {
      System.out.println("secret.txt created successfully.");
    } else {
      System.out.println("secret.txt already exists.");
    }
    // Write to secret.txt file
    String content = "This is a top-secret message.";
    FileWriter fw = new FileWriter(f);
    fw.write(content);
    fw.close();
    System.out.println("Content written to secret.txt");

    // Restrict access to the file
    if (f.setReadable(false) && f.setWritable(false)) {
      System.out.println("secret.txt permissions restricted.");
    } else {
      System.out.println("Failed to restrict secret.txt");
    }
  }
}