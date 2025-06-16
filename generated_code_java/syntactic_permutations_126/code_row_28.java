import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
  public void doGet(HttpServletRequest request,
                    HttpServletResponse response)
      throws ServletException, IOException {
    // Read the username from the request body into a String
    String name = request.getParameter("username");

    // Construct an HTML page as a string
    StringBuilder sb = new StringBuilder();
    sb.append("<html><body>");
    sb.append("<h1>Hello, " + name + "</h1>");
    sb.append("</body></html>");

    // Write the response body as an HTML page
    PrintWriter out = response.getWriter();
    out.print(sb);
    out.flush();

    // Close the writer and the HTTP connection
    out.close();
  }
}