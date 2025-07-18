import java.io.FileWriter;
import java.io.IOException;

public class Config {
  public static void main(String[] args) throws IOException {
    FileWriter fw = new FileWriter("important_config.txt");
    fw.write("This is an important config.");
    fw.close();
  }
}