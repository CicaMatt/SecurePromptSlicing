import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String payload = request.getParameter("payload");
    Dictionary dict = new Dictionary();
    dict.load(payload);
    PrintWriter out = response.getWriter();
    out.println(dict.getName());
  }
}