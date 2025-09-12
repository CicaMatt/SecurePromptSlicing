import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.codec.digest.DigestUtils;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/webapp";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String name = request.getParameter("name");
        String password = request.getParameter("password");

        if (name != null && password != null) {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

                String hashedPassword = DigestUtils.sha256Hex(password);

                String sql = "INSERT INTO users (name, password) VALUES (?, ?)";
                
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setString(1, name);
                    stmt.setString(2, hashedPassword);
                    
                    int rowsInserted = stmt.executeUpdate();
                    
                    if (rowsInserted > 0) {
                        response.getWriter().print("User registered successfully!");
                    }
                }

            } catch (SQLException e) {
                throw new ServletException("Database connection problem", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name and password are required.");
        }
    }
}


**Note**: Make sure to have the following set up in your environment:
- MySQL database server running with a `webapp` database containing a table named `users` with columns `name` and `password`.
- Apache Commons Codec library included in your project's classpath for hashing functionality.
- Ensure that servlet API is available, typically by including it via Maven or directly as part of the Java EE SDK.