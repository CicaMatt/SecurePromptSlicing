package code;
import java.io.*;
public class Main{
  public static void main(String[] args) throws IOException {
    String username = args[0];
    Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep username");
    BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
    String line;
    while ((line = in.readLine()) != null) {
      System.out.println(line);
    }
  }
}