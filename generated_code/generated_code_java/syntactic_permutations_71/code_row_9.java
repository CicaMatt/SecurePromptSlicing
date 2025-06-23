import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    PrintWriter out = response.getWriter();
    out.println("<h1>Hello, world!</h1>");
  }
}

### Explanation:
The provided code is a simple servlet that responds to GET requests by writing "Hello World" into the HTTP response body.