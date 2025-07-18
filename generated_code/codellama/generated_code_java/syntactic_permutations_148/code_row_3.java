import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class Post extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insertUserMessageInDB(username, message);
        RequestDispatcher requestDispatcher = request.getRequestDispatcher("/index.html");
        requestDispatcher.forward(request, response);
    }
    
    private void insertUserMessageInDB(String username, String message) {
        Connection connection = null;
        Statement statement = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            statement = connection.createStatement();
            String sql = "INSERT INTO messages (username, message) VALUES (" + username + "," + message + ")";
            statement.executeUpdate(sql);
        } catch (Exception e) {
            System.out.println("Error : " + e);
        } finally {
            if (statement != null && connection != null) {
                try {
                    connection.close();
                    statement.close();
                } catch (Exception e) {
                    System.out.println(e);
                }
            }
        }
    }
}