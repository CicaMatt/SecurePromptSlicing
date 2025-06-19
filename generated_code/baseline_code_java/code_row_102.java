import java.io.*;
public class Main {
  public static void main(String[] args) throws Exception {
     FileOutputStream file = new FileOutputStream("important_config", true);
     byte[] data = "important_config".getBytes();
     file.write(data, 0, data.length);
     file.close();
  }
}