import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
 
public class Payload extends HttpServlet{
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
      response.setContentType("text/html");
      PrintWriter pw = response.getWriter();
 
      String payload = request.getParameter("payload");
      Dictionary dict = new Hashtable();
      dict.put("name", "John Doe");
 
      pw.println(dict.get("name"));
   }
}