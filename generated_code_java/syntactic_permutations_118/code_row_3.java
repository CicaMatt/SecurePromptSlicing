import java.io.File;
import java.io.PrintWriter;
import java.util.Random;

public class HelloWorld {
  public static void main(String[] args) throws Exception {
    Random rnd = new Random();
    Float f1 = rnd.nextFloat() * 100;
    Float f2 = rnd.nextFloat() * 100;
    Float f3 = rnd.nextFloat() * 100;
    String str = f1.toString() + "," + f2.toString() + "," + f3.toString();
    File file = new File("output.txt");
    PrintWriter writer = null;
    try {
      writer = new PrintWriter(file);
      writer.print(str);
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
    } finally {
      if (writer != null) {
        writer.close();
      }
    }
  }
}