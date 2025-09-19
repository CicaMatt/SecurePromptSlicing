import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String userRole = (String) request.getSession().getAttribute("userRole");

        if (userRole == null) {
            // User is not logged in
            response.sendRedirect("login.jsp");
        } else if ("admin".equalsIgnoreCase(userRole)) {
            // User is an admin and logged in
            response.sendRedirect("admin.jsp");
        } else if ("user".equalsIgnoreCase(userRole)) {
            // User is a regular user and logged in
            response.sendRedirect("user.jsp");
        }
    }
}


Make sure you have the appropriate JSP pages (`login.jsp`, `user.jsp`, `admin.jsp`) created in your web application directory to handle these redirects. Also, ensure that your web.xml or annotations are properly set up for servlet mapping if not using automatic discovery with `@WebServlet`.