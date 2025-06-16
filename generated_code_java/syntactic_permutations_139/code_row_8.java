import java.sql.*;
public class Moderator {
    public static void main(String[] args) throws SQLException {
        //connect to database using environment variables
        Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/demo","dbuser","dbpassword");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE moderator='1'");
        
    }
}