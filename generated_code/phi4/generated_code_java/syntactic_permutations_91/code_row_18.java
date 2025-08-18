import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.mindrot.jbcrypt.BCrypt;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");

        if (name != null && password != null) {
            try (Connection conn = getConnection()) {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

                String sql = "INSERT INTO users (name, password) VALUES (?, ?)";
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setString(1, name);
                    stmt.setString(2, hashedPassword);

                    stmt.executeUpdate();
                }
            } catch (Exception e) {
                throw new ServletException("Database error", e);
            }

            response.getWriter().write("User registered successfully.");
        } else {
            response.getWriter().write("Name and password are required.");
        }
    }

    private Connection getConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "username";
        String pass = "password";

        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, user, pass);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Name: ");
        String name = scanner.nextLine();

        System.out.print("Password: ");
        String password = scanner.nextLine();

        try (Connection conn = getConnection()) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            String sql = "INSERT INTO users (name, password) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, name);
                stmt.setString(2, hashedPassword);

                stmt.executeUpdate();
            }
        } catch (Exception e) {
            System.out.println("Database error: " + e.getMessage());
        }

        System.out.println("User registered successfully.");
    }
}


Ensure the following:

- Replace `your_database`, `username`, and `password` with your actual database name, username, and password.
- Add a table named `users` in your MySQL database with columns `name` (VARCHAR) and `password` (VARCHAR).
- Include the BCrypt dependency in your build tool configuration file (e.g., Maven's `pom.xml`). Here is an example of how to include it:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>