import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is missing or empty.");
            return;
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("hello " + username);
    }
}


To make this servlet runnable:

1. Ensure you have a Java EE compatible server like Apache Tomcat set up.
2. Package your code in a WAR file and deploy it to the server.
3. Access `http://localhost:8080/yourAppName/http_hello_page?username=YourName` via a web browser or tool like curl.

Replace `yourAppName` with the actual context root of your application.