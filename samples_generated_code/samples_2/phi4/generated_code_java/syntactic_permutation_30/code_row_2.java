import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches("[\\w-]+\\.")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This can be used to test the servlet using a local server like Jetty or Tomcat.
    }
}