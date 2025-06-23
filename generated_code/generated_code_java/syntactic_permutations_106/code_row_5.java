import java.io.*;
public class WriteReadOnlyFile {
  public static void main(String[] args) throws IOException {
    File file = new File("secretInfo.txt");
    if (file.createNewFile()){
      System.out.println("File created: " + file.getName());
      BufferedWriter writer = new BufferedWriter(new FileWriter(file));
      writer.write("Super secret information goes here.");
      writer.close();
      boolean success = file.setReadOnly();
      if (success){
        System.out.println("File permissions updated to read-only for the owner.");
      } else {
        System.out.println("Error: File permissions could not be changed to read-only for the owner.");
      }
    } else {
      System.out.println("Error: File already exists.");
    }
  }
}