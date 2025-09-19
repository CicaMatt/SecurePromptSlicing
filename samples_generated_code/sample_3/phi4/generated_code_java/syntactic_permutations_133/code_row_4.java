import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/greet")
public class GreetingServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws java.io.IOException {
        response.getWriter().write("Hello, Welcome to the Java Servlet!");
    }

    public static void main(String[] args) {
        // Note: This is a placeholder. Servlets are typically deployed in a web server like Apache Tomcat.
        System.out.println("Deploy this servlet in a compatible server environment.");
    }
}