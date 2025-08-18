import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("https://www.example.com");
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder for running the servlet in a local server setup.
        // Typically, you would use a framework like Jetty or Tomcat to deploy this servlet.
    }
}