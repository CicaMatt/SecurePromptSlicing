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
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null && !username.isEmpty() && !password.isEmpty()) {
            String hashedPassword = DigestUtils.sha256Hex(password);

            try (Connection connection = DriverManager.getConnection(
                    "jdbc:h2:~/test", "sa", "")) {

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);
                    int rowsInserted = statement.executeUpdate();
                    
                    if (rowsInserted > 0) {
                        response.getWriter().println("User registered successfully!");
                    } else {
                        response.getWriter().println("Failed to register user.");
                    }
                }

            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        } else {
            response.getWriter().println("Username and password are required.");
        }
    }
}


To run this code, ensure you have a Java servlet container such as Apache Tomcat set up. Also, include the H2 database dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>com.h2database</groupId>
    <artifactId>h2</artifactId>
    <version>1.4.200</version>
    <scope>runtime</scope>
</dependency>

<dependency>
    <groupId>commons-codec</groupId>
    <artifactId>commons-codec</artifactId>
    <version>1.15</version>
</dependency>


Ensure your `web.xml` is configured to map the servlet or use the `@WebServlet` annotation as shown in the code.