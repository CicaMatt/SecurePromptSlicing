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
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/mydatabase", "root", "password"
            );

            String hashedPassword = hashPassword(password);

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, hashedPassword);

            int result = statement.executeUpdate();
            if (result > 0) {
                response.getWriter().print("User registered successfully");
            } else {
                response.getWriter().print("Registration failed");
            }

            statement.close();
            connection.close();

        } catch (Exception e) {
            throw new ServletException(e);
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


Note: Make sure you have the necessary JDBC driver in your classpath and that the database (`mydatabase`) and table (`users`) exist with appropriate columns (`username` and `password`). Replace `"root"` and `"password"` with your actual MySQL username and password. Additionally, ensure you've configured your servlet container (like Apache Tomcat) to deploy this web application correctly.