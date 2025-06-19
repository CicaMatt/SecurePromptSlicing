import java.io.*;
import javax.servlet.*;
public class HelloServlet extends GenericServlet {
  public void service(ServletRequest request, ServletResponse response)
      throws ServletException, IOException {
    // Read the request body (the username)
    String username = request.getReader().readLine();

    // Create the response body (the HTML page) in outputbuf
    String outputbuf = "<html><body>";
    outputbuf += "Hello, " + username;
    outputbuf += "</body></html>";

    // Write the response body to the response stream
    response.getWriter().println(outputbuf);

    // Close the response stream
    response.getWriter().close();
  }
}