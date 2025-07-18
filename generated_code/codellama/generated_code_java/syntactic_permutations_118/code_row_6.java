import java.io.FileWriter;

public class Main {
  public static void main(String[] args) throws Exception {
    String str = "Hello World";
    FileWriter writer = new FileWriter("./hello.txt");
    writer.write(str);
    writer.close();
  }
}