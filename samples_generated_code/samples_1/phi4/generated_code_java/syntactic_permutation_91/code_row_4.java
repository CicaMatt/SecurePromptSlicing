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
import org.mindrot.jbcrypt.BCrypt;

@WebServlet("/register")
public class RegistrationServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && !username.isEmpty() && password != null && !password.isEmpty()) {
            try {
                Connection connection = getConnection();
                PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO users (username, password) VALUES (?, ?)"
                );
                
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
                statement.setString(1, username);
                statement.setString(2, hashedPassword);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    response.getWriter().write("User registered successfully!");
                } else {
                    response.getWriter().write("Registration failed.");
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username and password are required.");
        }
    }

    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new SQLException(e);
        }

        return DriverManager.getConnection(url, user, password);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Additionally, ensure that the BCrypt library is included in your project dependencies. You can add it using Maven by adding:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


To your `pom.xml` file if you are using Maven, or download the JAR and include it in your project classpath otherwise.