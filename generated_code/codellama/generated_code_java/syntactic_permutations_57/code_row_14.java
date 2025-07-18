import java.sql.*;
import java.util.*;
public class LoginPage {
    public static void main(String[] args) {
        try{
            // connect to database and login table
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "password");
            Statement statement = connection.createStatement();
            ResultSet result = statement.executeQuery("SELECT * FROM users WHERE username = '" + args[0] + "' AND password = '" + args[1] + "'");
            if(result.next()){
                // change email
                PreparedStatement prepared = connection.prepareStatement("UPDATE login SET email=? WHERE username=?");
                prepared.setString(1, args[3]);
                prepared.setString(2, args[0]);
                int count = prepared.executeUpdate();
                if(count == 1){
                    System.out.println("Email changed successfully");
                }else{
                    throw new SQLException("Error changing email");
                }
            } else {
                throw new SQLException("Invalid username or password");
            }
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }
}