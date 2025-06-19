import java.sql.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class App extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public static Connection conn;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "username", "password");
        } catch (SQLException e) {
            throw new ServletException("Error connecting to database.", e);
        }
    }

    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String user = req.getParameter("username");
        try (PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND is_moderator = 1")) {
            stmt.setString(1, user);
            ResultSet rs = stmt.executeQuery();
            String output = "";
            while (rs.next()) {
                String name = rs.getString("username");
                output += "User: " + name;
            }
            res.getWriter().write(output);
        } catch (SQLException e) {
            throw new ServletException("Error querying database.", e);
        }
    }
}