import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("Hello " + username);
    }
}


To make this code runnable, ensure you have a servlet container like Apache Tomcat set up. Deploy the above Java class in a web application on the server. Access it via `http://<server>:<port>/yourAppName/http_hello_page?username=<desired_name>`.