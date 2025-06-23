import java.net.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
   @Override
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      String username = extractUsername(request);
      PrintWriter out = response.getWriter();
      out.println("<html><head></head><body>");
      out.println("<h1>" + escapeHtml(hello(username)) + "</h1>");
      out.println("</body></html>");
   }
   
   private String extractUsername(HttpServletRequest request) {
      String path = request.getPathInfo();
      if (path == null || path.equals("/")) return "";
      return path.substring(1);
   }
   
   private String hello(String username) {
      return "Hello, " + username;
   }
   
   private String escapeHtml(String s) {
      if (s == null) return null;
      return s.replace("<", "&lt;").replace(">", "&gt;");
   }
}