import java.lang.*;
public class PingDecorator {
  public static String ping(String url) {
    String output = "";
    try {
      Process p = Runtime.getRuntime().exec("ping -c2 " + url);
      BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
      String line = "";
      while ((line = input.readLine()) != null) {
        output += (line + "\n");
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
    return output;
  }
}