import java.sql.*;

public class Login {
    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database_name", "username", "password");
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT username, password FROM table_name WHERE username='" + args[0] + "' AND password='" + args[1] + "'");
        if (resultSet.next()) {
            response.sendRedirect("success");
        } else {
            response.sendRedirect("can't login");
        }
    } catch (Exception e) {
        response.sendRedirect("internal server error");
    }
}