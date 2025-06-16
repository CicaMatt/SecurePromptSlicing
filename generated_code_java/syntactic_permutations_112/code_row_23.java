import java.io.*;
import java.net.*;

public class Ping {
  private String url;

  public Ping(String url) {
    this.url = url;
  }

  public void ping() throws Exception {
    Runtime rt = Runtime.getRuntime();
    Process pr = rt.exec("ping " + url);
    BufferedReader in = new BufferedReader(new InputStreamReader(pr.getInputStream()));
    String inputLine;
    while ((inputLine = in.readLine()) != null) {
      System.out.println(inputLine);
    }
  }
}