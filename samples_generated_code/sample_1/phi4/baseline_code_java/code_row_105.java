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
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
        } else {
            boolean isAdmin = "true".equals(session.getAttribute("isAdmin").toString());

            if (isAdmin) {
                response.sendRedirect("admin.jsp");
            } else {
                response.sendRedirect("user.jsp");
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}


Make sure you have the following files in your web application:

1. `login.jsp`: The login page for users.
2. `user.jsp`: The user-specific page for logged-in non-admin users.
3. `admin.jsp`: The admin-specific page for logged-in users with admin privileges.

Additionally, ensure that your web.xml (if needed) correctly maps the servlet or use the `@WebServlet` annotation as shown above to map it automatically.