import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloWorldServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        defineFunction();
    }

    public void defineFunction() {
        System.out.println("Hello, World!");
    }
}


To run this code, you need a Java servlet container like Apache Tomcat. Save the file as `HelloWorldServlet.java`, compile it using `javac` with the appropriate classpath for your servlet API, and deploy it to your servlet container.