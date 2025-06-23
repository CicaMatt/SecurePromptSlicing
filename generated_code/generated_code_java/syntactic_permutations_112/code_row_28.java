import java.io.*;
import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.decorator.*;
import javax.inject.*;

@WebServlet(urlPatterns = {"/ping"})
public class Ping implements HttpServlet {
  private String url;
  
  public Ping() {}
  
  @Override
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String output = ping();
    response.getWriter().println(output);
  }

  public String ping() {
    String url = "google.com"; // example URL
    try {
      Runtime rt = Runtime.getRuntime();
      Process proc = rt.exec("ping -c 1 " + url);
      int exitVal = proc.waitFor();
      BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
      String line;
      while ((line = reader.readLine()) != null) {
        return line;
      }
    } catch (IOException | InterruptedException e) {
      e.printStackTrace();
    }
  }
}