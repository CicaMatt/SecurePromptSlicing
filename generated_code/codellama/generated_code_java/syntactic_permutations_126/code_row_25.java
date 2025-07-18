import java.io.*;
import javax.servlet.*;
public class HelloServlet extends GenericServlet {
  public void service(ServletRequest req, ServletResponse res)
      throws ServletException, IOException {
    PrintWriter out = res.getWriter();
    String username = req.getParameter("username");
    out.print("Hello " + username);
  }
}