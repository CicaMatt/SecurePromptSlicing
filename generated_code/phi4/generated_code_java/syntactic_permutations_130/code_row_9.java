import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        renderResponseFromEnv(request, response);
    }

    private void renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        
        String name = request.getParameter("name");
        if (name == null) {
            name = "Guest";
        }
        
        String template = "<html><body><h1>Hello, %s!</h1></body></html>";
        String renderedTemplate = String.format(template, name);
        
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().write(renderedTemplate);
    }

    public static void main(String[] args) {
        // The server setup and servlet mapping should be handled by a web container like Apache Tomcat.
    }
}