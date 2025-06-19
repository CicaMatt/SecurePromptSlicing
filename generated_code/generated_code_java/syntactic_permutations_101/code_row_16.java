import java.io.*;

class Main {
  public static void main(String[] args) throws Exception{
    File f = new File("important_config");
    BufferedWriter bw = new BufferedWriter(new FileWriter(f));
    String content = "important_config";
    bw.write(content);
    bw.close();
  }
}