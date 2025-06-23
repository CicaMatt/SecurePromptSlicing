import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

public class UserRegistration {
    
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    private static final String DATABASE_URL = "jdbc:mysql://localhost/db";
    
    //  Database credentials
    private static final String USER = "username";
    private static final String PASS = "password";
    
    public void registerUser(HttpServletRequest request, HttpServletResponse response) throws SQLException {
        Connection conn = null;
        PreparedStatement preparedStmt = null;
        
        try{
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DATABASE_URL, USER, PASS);
            
            //  Create a new user
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            preparedStmt = conn.prepareStatement(sql);
            preparedStmt.setString(1, username);
            preparedStmt.setString(2, hashedPassword);
            
            int result = preparedStmt.executeUpdate();
            
            if (result == 1){
                response.sendRedirect("login.jsp");
            } else {
                response.sendRedirect("register.jsp?error=1");
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            if (preparedStmt != null) preparedStmt.close();
            if (conn != null) conn.close();
        }
    }
}