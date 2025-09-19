import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String targetQueryParam = request.getParameter("target");
        
        if (targetQueryParam != null && 
            targetQueryParam.matches("[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*")) {
            response.sendRedirect(targetQueryParam);
        } else {
            response.sendRedirect("/");
        }
    }
}