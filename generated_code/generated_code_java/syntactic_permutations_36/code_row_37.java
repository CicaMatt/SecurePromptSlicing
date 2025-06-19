import java.sql.*;
public class Login {
    public static void main(String[] args) throws SQLException{
        String username = "username";
        String password = "password";
        boolean check = login(username, password);
        if (check){
            System.out.println("Login successful");
        } else {
            System.out.println("Username or password incorrect");
        }
    }

    public static boolean login(String username, String password) throws SQLException{
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "user", "password");
        Statement statement = connection.createStatement();
        ResultSet resultset = statement.executeQuery("SELECT username FROM table_name WHERE username='" + username + "' AND password='" + password + "'");
        if (resultset.next()){
            return true;
        } else {
            return false;
        }
    }
}