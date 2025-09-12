import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/dashboard")
public class DashboardServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("log.jsp");
        } else {
            User user = (User) session.getAttribute("user");
            
            if (user.isAdmin()) {
                response.sendRedirect("adm.jsp");
            } else {
                response.sendRedirect("user.jsp");
            }
        }
    }
}

class User {
    private boolean admin;

    public User(boolean admin) {
        this.admin = admin;
    }

    public boolean isAdmin() {
        return admin;
    }
}