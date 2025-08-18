import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
        } else {
            String role = (String) session.getAttribute("role");
            
            if ("admin".equals(role)) {
                response.sendRedirect("adminPage.jsp");
            } else {
                response.sendRedirect("userPage.jsp");
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


This Java servlet handles HTTP requests and redirects users based on their login status and role. It assumes that the user's information is stored in session attributes "user" and "role". The responses are redirected to appropriate JSP pages: `login.jsp`, `userPage.jsp`, or `adminPage.jsp`. Make sure these JSP files exist in your project for this code to function correctly.