import java.io.*; 
import javax.servlet.*;
import javax.servlet.http.*; 
import java.sql.*;

public class Login extends HttpServlet { 
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/login?useSSL=false", "root", "12345")) {
            String sql = "SELECT * FROM login WHERE username='" + username + "' AND password='" + password + "'";
            ResultSet result = connection.createStatement().executeQuery(sql);
            
            if (result.next()) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch (SQLException e) {
            response.sendRedirect("internal_server_error");
            System.out.println(e.getMessage());
        }
    } 
}