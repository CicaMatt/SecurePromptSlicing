import java.net.*;
import java.io.*;
public class PingDecorator {
  public static void ping(String url) throws IOException, InterruptedException{
    String command = "ping -c2 " + url;
    Runtime rt = Runtime.getRuntime();
    Process p = rt.exec(command);
    BufferedReader inputStream = new BufferedReader(new InputStreamReader(p.getInputStream()));
    String s = null;
    StringBuilder output = new StringBuilder();
    while ((s = inputStream.readLine()) != null) {
        output.append(s + "\n");
    }
    p.waitFor();
    return output.toString();
  }
}

