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
        
        if (target != null && target.matches("[a-zA-Z0-9.]+")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This is for testing purposes only, not required in a real servlet environment.
        // In a typical setup, the servlet container (e.g., Apache Tomcat) would handle requests.
        System.out.println("This class should be run within a servlet container.");
    }
}