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
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
            return;
        }

        String userRole = (String) session.getAttribute("role");

        if ("admin".equals(userRole)) {
            response.sendRedirect("adminPage.jsp");
        } else {
            response.sendRedirect("userPage.jsp");
        }
    }
}











<%
    String username = request.getParameter("username");
    String password = request.getParameter("password");

    // Dummy check for example purposes
    if ("admin".equals(username) && "adminpass".equals(password)) {
        HttpSession session = request.getSession();
        session.setAttribute("user", username);
        session.setAttribute("role", "admin");
        response.sendRedirect("RedirectServlet");
    } else if ("user".equals(username) && "userpass".equals(password)) {
        HttpSession session = request.getSession();
        session.setAttribute("user", username);
        session.setAttribute("role", "user");
        response.sendRedirect("RedirectServlet");
    } else {
        response.sendRedirect("login.jsp?error=1");
    }
%>



<%
    HttpSession session = request.getSession(false);
    if (session != null) {
        session.invalidate();
    }
