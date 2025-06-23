import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
public class HelloWorld extends HttpServlet {
  public void doGet(HttpServletRequest request,
                    HttpServletResponse response)
            throws ServletException, IOException {
    PrintWriter out = response.getWriter();
    String greeting = "Hello World!";
    if (request.getParameter("user") != null) {
      String userName = request.getParameter("user");
      greeting = "Hello " + userName;
    }
    out.println("<html><body>");
    out.println(greeting);
    out.println("</body></html>");
  }
}