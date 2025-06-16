import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class PingServlet extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
    String url = req.getParameter("url");
    Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
    BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
    String inputLine;
    StringBuilder response = new StringBuilder();
    while ((inputLine = in.readLine()) != null) {
      response.append(inputLine);
    }
    in.close();
    resp.setContentType("text/plain");
    PrintWriter out = resp.getWriter();
    out.println(response.toString());
  }
}