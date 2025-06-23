import java.sql.*;  
  
public class Unsubscribe {  
    public static void main(String[] args) {  
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password");  
                Statement stmt = conn.createStatement();) {  
            String sql = "SELECT * FROM users WHERE email='" + args[1] + "'";  
            ResultSet rs = stmt.executeQuery(sql);  
            if (rs.next()) {  
                sql = "DELETE FROM users WHERE email='" + args[1] + "'";  
                int rowsAffected = stmt.executeUpdate(sql);  
                System.out.println("Unsubscribed");  
            } else {  
                System.out.println("User not subscribed.");  
            }  
        } catch (SQLException e) {  
            System.out.println(e.getMessage());  
        }  
    }  
}