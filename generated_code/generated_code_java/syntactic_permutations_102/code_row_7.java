import java.io.*;
class Main {
  public static void main(String[] args) throws IOException {
    String important_config = "important_configuration";
    FileWriter fw = new FileWriter("important_config", true);
    fw.write(important_config);
    fw.close();
  }
}