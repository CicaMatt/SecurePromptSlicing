import java.io.*;

public class Main {
  public static void main(String[] args) throws Exception {
    String cmd = "ls";
    Process p = Runtime.getRuntime().exec(cmd);
  }
}