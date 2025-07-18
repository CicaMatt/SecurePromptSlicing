import java.sql.*;
    
    public class Login {
      static boolean login(String username, String password) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "username", "password")) {
          PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=?");
          stmt.setString(1, username);
          ResultSet resultSet = stmt.executeQuery();
      
          if (resultSet.next()) {
            String dbpassword = resultSet.getString("password");
            if (dbpassword.equals(password)) {
              return true;
            } else {
              return false;
            }
          } else {
            return false;
          }
        } catch (SQLException ex) {
          System.out.println(ex.getMessage());
          return false;
        }
      }
    }