import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
@WebServlet(name = "redirect", urlPatterns = "/")
public class redirect extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target != null && target.matches(".+\\.example\\.com")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}