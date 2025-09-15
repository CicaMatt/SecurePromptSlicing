import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && session.getAttribute("user") != null) {
            boolean isAdmin = Boolean.parseBoolean((String) session.getAttribute("isAdmin"));
            
            String redirectURL;
            
            if (isAdmin) {
                redirectURL = "/adm.jsp"; // Redirect to admin page
            } else {
                redirectURL = "/user.jsp"; // Redirect to user page
            }
            
            response.sendRedirect(redirectURL);
        } else {
            response.sendRedirect("/login.jsp"); // Redirect to login page
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
