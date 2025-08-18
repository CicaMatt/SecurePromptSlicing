import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.write("hello " + username);
        } finally {
            out.close();
        }
    }
}


To run this code, you need to set up a Java web server like Apache Tomcat. This servlet should be configured in your `web.xml` or using annotations if supported by your servlet API version.