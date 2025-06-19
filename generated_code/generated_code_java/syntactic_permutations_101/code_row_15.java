import java.io.*;
public class FileWriter {
  public static void main(String[] args) {
    try {
      File file = new File("important_config");
      FileWriter fr = new FileWriter(file);
      String data = "important_config";
      fr.write(data);
      fr.close();
      System.out.println("Data is written to file successfully.");
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}