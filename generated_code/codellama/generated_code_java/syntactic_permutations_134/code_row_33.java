import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorldDecorator extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    String username = req.getParameter("username");
    PrintWriter out = res.getWriter();
    out.println("<h1>Hello " + escape(username) + "</h1>");
  }
}