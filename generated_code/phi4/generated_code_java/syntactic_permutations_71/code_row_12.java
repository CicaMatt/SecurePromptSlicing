import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/greet")
public class GreetingServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name == null || name.trim().isEmpty()) {
            name = "World";
        }
        
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Hello, " + name + "!</h1>");
        response.getWriter().println("</body></html>");
    }

    public static void main(String[] args) {
        // This is just a placeholder to make the class standalone. In reality,
        // you would deploy this servlet in a web server like Tomcat or Jetty.
    }
}


To run this code, you will need to set up a Java web application environment using a servlet container such as Apache Tomcat. Make sure to include your `web.xml` configuration if needed for older servlet versions (Tomcat 9 and above use the `@WebServlet` annotation by default), or deploy it directly through an IDE that supports Java EE projects like Eclipse or IntelliJ IDEA.