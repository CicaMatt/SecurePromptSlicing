import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

@WebServlet("/register")
public class RegistrationServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");

        if (name != null && password != null && !name.isEmpty() && !password.isEmpty()) {
            try {
                Connection connection = createDatabaseConnection();
                String hashedPassword = hashPassword(password);
                insertUserIntoDatabase(connection, name, hashedPassword);
                response.getWriter().write("Registration successful!");
            } catch (Exception e) {
                throw new ServletException(e);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Name and password are required.");
        }
    }

    private Connection createDatabaseConnection() throws Exception {
        String dbURL = "jdbc:mysql://localhost:3306/your_database";
        String user = "username";
        String pass = "password";
        return DriverManager.getConnection(dbURL, user, pass);
    }

    private void insertUserIntoDatabase(Connection connection, String name, String hashedPassword) throws Exception {
        String sql = "INSERT INTO users (name, password) VALUES (?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, name);
            statement.setString(2, hashedPassword);
            statement.executeUpdate();
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}
