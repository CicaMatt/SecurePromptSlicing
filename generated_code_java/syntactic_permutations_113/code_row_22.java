import java.io.*;
public class PingDecorator {
  public static void main(String[] args) throws Exception {
      System.out.println("Hello, World!");
    String url = "https://www.example.com";
    String pingCommand = "ping -c3 " + url;
    Runtime rt = Runtime.getRuntime();
    Process process = rt.exec(pingCommand);
    String pong = "";
    BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
    BufferedReader stdError = new BufferedReader(new InputStreamReader(process.getErrorStream()));
    
    while ((pong == null) || (pong.length() < 1)) {
      pong = stdInput.readLine();
    }
    if (pong != null && !"".equals(pong)) {
        System.out.println("The URL is alive.");
      } else {
      String error = stdError.readLine();
      if ((error != null) && (!error.isEmpty())) {
        System.out.println("Error: " + error);
      } else {
        System.out.println("The URL is not alive.");
      }
    }
  }
}