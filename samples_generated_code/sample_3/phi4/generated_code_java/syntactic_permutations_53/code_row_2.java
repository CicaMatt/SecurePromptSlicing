import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/AccessControl")
public class AccessControl extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        String role = (session != null) ? (String) session.getAttribute("role") : null;

        if (session == null || role == null) {
            redirectToLoginPage(response);
        } else {
            switch (role.toLowerCase()) {
                case "user":
                    redirectToUserPage(response);
                    break;
                case "admin":
                    redirectToAdminPage(response);
                    break;
                default:
                    redirectToLoginPage(response);
                    break;
            }
        }
    }

    private void redirectToLoginPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("login.jsp");
    }

    private void redirectToUserPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("userpage.jsp");
    }

    private void redirectToAdminPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("adminpage.jsp");
    }
}


Make sure that you have the necessary JSP files (`login.jsp`, `userpage.jsp`, and `adminpage.jsp`) in your web application to handle these redirects.