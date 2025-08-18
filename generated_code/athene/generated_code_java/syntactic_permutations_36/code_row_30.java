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
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.sendRedirect("home.jsp");
        } else {
            response.getWriter().println("Login failed. Please try again.");
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    private boolean authenticate(String username, String password) {
        final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
        final String USER = "dbuser";
        final String PASS = "dbpassword";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM users WHERE username = ?";
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                return password.equals(rs.getString("password"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}