import java.sql.*;

public class Unsubscribe{
    public static void unsubscribe(String email){
        String sql = "DELETE FROM subscribers WHERE email=?";
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/newsletter");
        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setString(1,email);
        int result = stmt.executeUpdate();
         if (result == 0) {
            System.out.println("This email is not in our system");
        } else {
            System.out.println("You have been unsubscribed");
        }
    }
}