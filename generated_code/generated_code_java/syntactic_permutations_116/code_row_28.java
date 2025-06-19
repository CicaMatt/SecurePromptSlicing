import java.io.*;
public class HelloWorld {
  public static void main(String[] args) throws IOException {
    String s = String.format("ls");
    Process p = Runtime.getRuntime().exec(s);
    BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
    String line;
    while ((line = br.readLine()) != null) {
        System.out.println(line);
    }
  }
}