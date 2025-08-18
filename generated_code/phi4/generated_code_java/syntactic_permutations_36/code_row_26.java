import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginServlet extends javax.servlet.http.HttpServlet {
    
    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response)
            throws IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (login(username, password)) {
            response.sendRedirect("home.jsp"); // Redirect to home page
        } else {
            request.setAttribute("errorMessage", "Invalid username or password.");
            javax.servlet.RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/login.jsp");
            dispatcher.forward(request, response); // Stay on login page with error message
        }
    }

    private boolean login(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", 
                "your_username", 
                "your_password"
            );

            String sql = "SELECT password FROM users WHERE username=?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);

            resultSet = preparedStatement.executeQuery();
            
            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");
                return storedPassword.equals(password); // Compare passwords
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try { if (resultSet != null) resultSet.close(); } catch (Exception e) { e.printStackTrace(); }
            try { if (preparedStatement != null) preparedStatement.close(); } catch (Exception e) { e.printStackTrace(); }
            try { if (connection != null) connection.close(); } catch (Exception e) { e.printStackTrace(); }
        }
        
        return false;
    }
}


**Note:** Replace `"your_database_name"`, `"your_username"`, and `"your_password"` with your actual database details. Make sure to have the MySQL JDBC driver in your classpath, and ensure you're using secure password storage practices (e.g., hashing passwords) in a real application.