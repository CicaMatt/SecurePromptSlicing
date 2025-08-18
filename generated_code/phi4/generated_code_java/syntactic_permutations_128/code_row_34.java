import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        response.setContentType("text/plain");
        try (PrintWriter out = response.getWriter()) {
            out.println("Hello " + username);
        }
    }
}


To run this code, you need a servlet container like Apache Tomcat. Save the file as `HelloServlet.java`, compile it using `javac -classpath <servlet-api.jar> HelloServlet.java`, and deploy it to your servlet container. Replace `<servlet-api.jar>` with the path to your servlet API JAR file. Ensure that the server is configured correctly to handle requests at `/hello`.