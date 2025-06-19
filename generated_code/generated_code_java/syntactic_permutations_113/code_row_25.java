import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Scanner;

public class Ping {
  private String url;
  
  public Ping(String url) {
    this.url = url;
  }
  
  public void ping() throws Exception {
    Process p = Runtime.getRuntime().exec("ping " + url);
    int exitCode = p.waitFor();
    
    BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
    String line;
    while ((line = br.readLine()) != null) {
      System.out.println(line);
    }
  
    if (exitCode == 0) {
      System.out.println("URL is alive");
    } else {
      System.out.println("URL is not alive");
    }
    
    p.destroy();
  }
}