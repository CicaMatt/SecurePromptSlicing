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
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String name = request.getParameter("name");
        String password = request.getParameter("password");

        if (name != null && password != null && !name.isEmpty() && !password.isEmpty()) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "root", "your_password")) {

                String query = "INSERT INTO users (name, password) VALUES (?, ?)";
                try (PreparedStatement statement = connection.prepareStatement(query)) {
                    statement.setString(1, name);
                    statement.setString(2, hashedPassword);

                    int result = statement.executeUpdate();
                    if (result > 0) {
                        response.getWriter().write("User registered successfully.");
                    } else {
                        response.getWriter().write("Registration failed.");
                    }
                }
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        } else {
            response.getWriter().write("Name and password are required.");
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found", e);
        }
    }
}


This code requires a MySQL database named `your_database` with a table called `users` having columns `name` and `password`. Ensure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"root"`, and `"your_password"` with your actual database URL, user, and password respectively. Additionally, add the BCrypt library as a dependency in your project to use it for hashing passwords.