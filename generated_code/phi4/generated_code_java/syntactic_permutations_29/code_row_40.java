import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    private static final String REGEX = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        String target = req.getParameter("target");
        
        if (target != null && target.matches(REGEX)) {
            resp.sendRedirect(target);
        } else {
            resp.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This method is not used in a servlet container. It's here to illustrate the complete runnable code.
    }
}