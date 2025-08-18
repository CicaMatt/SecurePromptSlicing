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

            if ("admin".equalsIgnoreCase(role)) {
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


Note: To make this servlet work, you need to set up a Java web application with the appropriate JSP pages (`login.jsp`, `adminPage.jsp`, `userPage.jsp`) and configure your server (like Apache Tomcat) properly. Also, ensure that session management is correctly implemented for user authentication and role assignment in your login process.