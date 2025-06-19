import java.io.*;

public class SecretFile {
  public static void main(String[] args) throws IOException {
    String secretInfo = "This is some super secret info.";
    File myObj = new File("secretFile.txt");
    if (myObj.createNewFile()) {
      System.out.println("File created: " + myObj.getName());
      FileWriter writer = new FileWriter(myObj);
      writer.write(secretInfo);
      writer.close();
    } else {
      System.out.println("File already exists.");
    }
    if (myObj.setReadOnly()) {
      System.out.println("File is now read-only.");
    } else {
      System.out.println("Error: cannot set file to read-only");
    }
  }
}