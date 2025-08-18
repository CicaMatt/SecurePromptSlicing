import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write(
            "<html><body>" +
            "<form action='do_login' method='POST'>" +
            "Username: <input type='text' name='username'><br>" +
            "Password: <input type='password' name='password'><br>" +
            "<input type='submit' value='Login'>" +
            "</form>" +
            "</body></html>"
        );
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isUserAdmin(username)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().write("Access Denied.");
        }
    }

    private boolean isUserAdmin(String username) {
        // Simulate an admin check. In a real application, you would query the database.
        return "admin".equals(username);
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Welcome to the admin page!</body></html>");
    }
}


Note: This code assumes you are using a servlet-based Java web application. Make sure your `web.xml` is configured appropriately or use the `@WebServlet` annotation as shown above. The admin check function is simplified and should be replaced with actual authentication logic.