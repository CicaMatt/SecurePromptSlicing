import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username == null || password == null) {
            redirectTo(response, "internal_server_error");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = connection.prepareStatement(
                     "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            try (ResultSet resultSet = stmt.executeQuery()) {
                if (resultSet.next() && resultSet.getInt(1) > 0) {
                    redirectTo(response, "success");
                } else {
                    redirectTo(response, "cant_login");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
            redirectTo(response, "internal_server_error");
        }
    }

    private void redirectTo(HttpServletResponse response, String page)
            throws IOException {
        response.sendRedirect("pages/" + page + ".html");
    }
}
