import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
public class HelloServlet extends HttpServlet {
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    PrintWriter out = response.getWriter();
    out.println("<h1>Hello " + escape(username) + "</h1>");
  }

  public static String escape(String s) {
    return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;");
  }
}