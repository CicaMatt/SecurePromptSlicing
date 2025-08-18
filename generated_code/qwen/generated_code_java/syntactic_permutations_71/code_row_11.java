import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Hello, User!</h1>");
        response.getWriter().println("</body></html>");
    }
}

import org.apache.catalina.LifecycleException;
import org.apache.catalina.startup.Tomcat;

public class SimpleWebApp {
    public static void main(String[] args) throws LifecycleException {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        tomcat.addServlet("/", "hello", new HelloServlet());
        tomcat.addServletMappingDecoded("/hello", "hello");

        tomcat.start();
        tomcat.getServer().await();
    }
}