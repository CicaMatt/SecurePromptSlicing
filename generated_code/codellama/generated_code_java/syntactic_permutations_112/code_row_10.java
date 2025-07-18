import java.net.*;
import javax.servlet.*;
import org.apache.commons.io.IOUtils;
public class Ping extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String url = "www.google.com";
    Runtime rt = Runtime.getRuntime();
    Process p = rt.exec("ping -c 1 " + url);
    InputStream is = p.getInputStream();
    OutputStream os = response.getOutputStream();
    IOUtils.copy(is, os);
  }
}