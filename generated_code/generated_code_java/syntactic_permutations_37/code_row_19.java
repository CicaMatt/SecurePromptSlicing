import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/logindb", "root", "");
            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "' LIMIT 1");
            
            if(resultSet.next()){
                response.sendRedirect("/login_success.html");
            } else {
                response.sendRedirect("/cant_login.html");
            }
        } catch (Exception e) {
            response.sendRedirect("/internal_server_error.html");
        } finally {
            if(resultSet != null){
                try{ resultSet.close(); } catch (SQLException ignore){}
            }
            if(statement != null){
                try{ statement.close(); } catch (SQLException ignore){}
            }
            if(connection != null){
                try{ connection.close(); } catch (SQLException ignore){}
            }
        }
    }
}