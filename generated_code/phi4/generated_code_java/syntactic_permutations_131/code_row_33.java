import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    private String env = "Welcome, {name}!";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        renderResponseFromEnv(request, response);
    }

    private void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            name = "Guest";
        }
        
        String template = env;
        String renderedTemplate = template.replace("{name}", name);
        
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

}


To run this code, you will need a servlet container like Apache Tomcat. Deploy the above servlet in your web application and access it via `http://localhost:8080/yourAppName/home?name=YourName`. Adjust the port and context path as necessary.