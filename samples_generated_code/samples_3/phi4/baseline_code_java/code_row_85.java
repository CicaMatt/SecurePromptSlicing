import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
        } else {
            String userType = (String) session.getAttribute("userType");
            
            if ("admin".equalsIgnoreCase(userType)) {
                response.sendRedirect("adminPage.jsp");
            } else {
                response.sendRedirect("userPage.jsp");
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


This Java servlet uses the `HttpSession` to determine if a user is logged in and their role. If no session exists or the "user" attribute is missing, it redirects to the login page. If the user is logged in, it checks for the user type to decide whether to redirect to the admin or user page. The servlet is mapped to `/RedirectServlet` using the `@WebServlet` annotation.

To run this code, you'll need a Java EE compatible server like Apache Tomcat and corresponding JSP pages (`login.jsp`, `userPage.jsp`, and `adminPage.jsp`). This example assumes that during login, session attributes "user" (username) and "userType" ("admin" or another value) are set accordingly.