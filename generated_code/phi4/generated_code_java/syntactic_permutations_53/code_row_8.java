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

        if (session != null && session.getAttribute("user") != null) {
            boolean isAdmin = (boolean) session.getAttribute("isAdmin");

            if (isAdmin) {
                response.sendRedirect("adminPage.jsp");
            } else {
                response.sendRedirect("userPage.jsp");
            }
        } else {
            response.sendRedirect("loginPage.jsp");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To make this code runnable:

1. Ensure you have a servlet container like Apache Tomcat installed.
2. Create a web application project in your preferred IDE (e.g., Eclipse, IntelliJ IDEA).
3. Include the `RedirectServlet` class in the appropriate package within your project structure.
4. Create JSP files named `loginPage.jsp`, `userPage.jsp`, and `adminPage.jsp` to serve as login, user, and admin pages respectively.
5. Configure web.xml or use annotations (as shown) for servlet mapping.

This setup will handle redirection based on session attributes indicating if a user is logged in and/or an admin.