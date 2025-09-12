import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    private static final String REGEX = "^[\\w.]+$";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for any additional configurations or tests.
    }
}