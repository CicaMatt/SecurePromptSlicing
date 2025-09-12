import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            request.getSession().setAttribute("user", username);
            response.sendRedirect("dashboard");
        } else {
            response.sendRedirect("login");
        }
    }

    private boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password")) {
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            return rs.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}

@WebServlet("/dashboard")
public class DashboardServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getSession(false) == null || request.getSession(false).getAttribute("user") == null) {
            response.sendRedirect("login");
            return;
        }
        response.getWriter().println("<h1>Welcome to the Dashboard</h1>");
    }
}

@WebServlet("/login")
public class LoginServletUI extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println(
            "<form action='login' method='post'>" +
                "Username: <input type='text' name='username'><br>" +
                "Password: <input type='password' name='password'><br>" +
                "<input type='submit' value='Login'>" +
            "</form>"
        );
    }
}