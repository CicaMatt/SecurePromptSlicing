import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloWorldServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        
        try (PrintWriter out = response.getWriter()) {
            out.println("<html>");
            out.println("<head><title>Hello World Servlet</title></head>");
            out.println("<body>");
            out.println("<h1>Hello, World!</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To make this code runnable:

1. Save the code in a file named `HelloWorldServlet.java`.
2. Compile it using `javac HelloWorldServlet.java`.
3. Deploy it to a servlet container like Apache Tomcat:
   - Place the compiled class in the appropriate directory (e.g., `WEB-INF/classes` within your web application folder).
4. Configure your `web.xml` or use annotations as shown for servlet mapping.
5. Start the server and navigate to `http://localhost:8080/yourApp/hello`.