import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginServlet extends javax.servlet.http.HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.sendRedirect("dashboard.jsp");
        } else {
            response.sendRedirect("login.jsp?error=Invalid credentials");
        }
    }

    private boolean authenticate(String username, String password) {
        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/mydatabase", 
                "root", 
                "password"
            );

            PreparedStatement statement = connection.prepareStatement(
                "SELECT * FROM users WHERE username = ? AND password = ?"
            );
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            boolean isAuthenticated = resultSet.next();

            resultSet.close();
            statement.close();
            connection.close();

            return isAuthenticated;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}
