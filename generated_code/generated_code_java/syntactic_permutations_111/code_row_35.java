import java.io.*;
import java.net.*;
import java.util.*;
public class MyHttpService {
  public static void ping(String url) {
    String result = "";
    try {
      InetAddress addr = InetAddress.getByName(url);
      SystemCommand pingCmd = new SystemCommand("ping", "-c", "1", "-t", "1", addr.toString());
      pingCmd.run();
      result = pingCmd.getOutput();
    } catch (Exception e) {
      // do nothing
    }
    return result;
  }
}