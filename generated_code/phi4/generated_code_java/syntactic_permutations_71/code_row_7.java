import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/HelloWorld")
public class HelloWorldServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public HelloWorldServlet() {
        super();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().append("<!DOCTYPE html>\n")
                .append("<html>\n")
                .append("<head><title>Hello World Servlet</title></head>\n")
                .append("<body>\n")
                .append("<h1>Hello, World!</h1>\n")
                .append("</body>\n")
                .append("</html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}


To run this code, you need a Java servlet container like Apache Tomcat. Deploy the above servlet as part of a web application in your servlet container's `webapps` directory. Make sure to include the necessary configuration files (e.g., `web.xml`) if needed by your environment or server setup.