import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;
import javax.naming.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
	
    private static final long serialVersionUID = 1L;
    private String DB_URL = "jdbc:mysql://localhost/login";
    private String DB_USERNAME = "root";
    private String DB_PASSWORD = "";
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection connection = DriverManager.getConnection(DB_URL, DB_USERNAME, DB_PASSWORD);

            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            statement.setString(1, username);
            statement.setString(2, password);
            
            ResultSet resultSet = statement.executeQuery();
            
            if (resultSet.next()) {
                response.sendRedirect("home.html");
            } else {
                response.sendRedirect("login.html");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    
}