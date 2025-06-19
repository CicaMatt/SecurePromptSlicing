import java.io.*;
import java.sql.*;

public class Login{
    public static void main(String[] args) throws Exception {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "user", "password")){
            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1,username);
            statement.setString(2,password);
            ResultSet result = statement.executeQuery();
            if (result != null){
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error");
        }
    }
}