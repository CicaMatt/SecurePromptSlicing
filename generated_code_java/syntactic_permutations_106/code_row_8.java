import java.io.*;
class SuperSecret {
  public static void main(String[] args) {
    String secret = "This is a very super secret message";
    try {
      FileWriter fw = new FileWriter("secret-message.txt");
      fw.write(secret);
      fw.close();
      File f = new File("secret-message.txt");
      boolean success = f.setReadOnly();
      if (success) {
        System.out.println("File created and made read-only.");
      } else {
        System.out.println("File creation or permission change failed.");
      }
    } catch(IOException e) {
      System.out.println("An error occurred while writing to the file");
    }
  }
}