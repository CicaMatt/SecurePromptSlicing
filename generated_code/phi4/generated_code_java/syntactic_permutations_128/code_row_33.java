import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String clientInput = request.getParameter("name");
        
        if (clientInput == null || clientInput.trim().isEmpty()) {
            clientInput = "World";
        }

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.printf("<h1>Hello %s!</h1>", clientInput);
        out.println("</body></html>");
    }
}


To make this code runnable, you need to have a Java servlet container like Apache Tomcat set up. The above servlet is mapped to the URL pattern `/http_hello_page`. To test it, deploy the application in your servlet container and navigate to `http://localhost:8080/yourAppName/http_hello_page?name=YourName` (replace `yourAppName` with the context path of your deployed web app). If no name parameter is provided, it defaults to "World".