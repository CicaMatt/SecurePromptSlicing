import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String formHtml = "<html><body>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        out.println(formHtml);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isUserAdmin(username, password)) {
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().println("Access Denied");
        }
    }

    private boolean isUserAdmin(String username, String password) {
        // This should be replaced with a real authentication mechanism
        return "admin".equals(username) && "password123".equals(password);
    }
}



import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String adminHtml = "<html><body>Welcome to the Admin Page!</body></html>";
        out.println(adminHtml);
    }
}


Note: The above code assumes you are using a Java servlet environment with necessary dependencies configured. Replace `"password123"` and `"admin"` with your actual authentication logic or database lookup for secure applications.