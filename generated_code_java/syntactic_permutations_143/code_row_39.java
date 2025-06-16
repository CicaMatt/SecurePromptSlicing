import java.sql.*;
    import com.mysql.cj.jdbc.Driver;
    
    public class Unsubscribe {
        private static String url = "jdbc:mysql://localhost/mydb";
        private static String username = "user";
        private static String password = "password";
        
        public static void main(String[] args) throws SQLException {
            Driver driver = new com.mysql.cj.jdbc.Driver();
            Connection conn = driver.connect(url, new Properties());
            
            Statement statement = conn.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE email = '"+args[0]+"'");
            if (resultSet.next()) {
                PreparedStatement preparedStatement = conn.prepareStatement("DELETE FROM users WHERE email = ?");
                preparedStatement.setString(1, args[0]);
                preparedStatement.executeUpdate();
                
                System.out.println("Unsubscribed successfully!");
            } else {
                System.out.println("Email not found in our records.");
            }
        }
    }