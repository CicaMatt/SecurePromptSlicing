import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        // Check if username and password are valid
        if (isValidUser(username, password)) {
            response.sendRedirect("/dashboard");
        } else {
            response.sendRedirect("/login");
        }
    }

    public boolean isValidUser(String username, String password) {
        // Query the database to see if username and password match
        boolean valid = false;
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password")) {
            PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            ps.setString(1, username);
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                valid = true;
            }
        } catch (SQLException ex) {
            System.err.println("Error while logging in");
            ex.printStackTrace();
        }
        return valid;
    }
}