import java.io.*;
import java.util.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        PrintWriter out = response.getWriter();
        
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "password");
             PreparedStatement statement = conn.prepareStatement(
                    "SELECT * FROM users WHERE username=? AND password=?")) {
            statement.setString(1, username);
            statement.setString(2, password);
            
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch (SQLException e) {
            out.println("Internal server error.");
            out.println(e);
        }
    }
}