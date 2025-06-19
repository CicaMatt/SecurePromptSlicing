import java.io.*;
public class Ping {
  public static void ping(HttpServletRequest request, HttpServletResponse response) throws IOException{
    String url = "https://www.google.com"; // URL to ping
    Runtime rt = Runtime.getRuntime();
    Process pr = rt.exec("ping " + url);
    InputStream instr = pr.getInputStream();
    OutputStream outstr = response.getOutputStream();
    int b;
    while ((b = instr.read()) != -1) {
      outstr.write(b);
    }
    outstr.close();
  }
}