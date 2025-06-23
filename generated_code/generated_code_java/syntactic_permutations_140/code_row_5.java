import java.sql.*;
public boolean isUsernameExist(String username){
    String sql = "SELECT * FROM USERS WHERE username = ?";
    Connection conn = null;
    try {
      conn = getConnection();
      PreparedStatement ps= conn.prepareStatement(sql);
      ps.setString(1,username);
      ResultSet rs=ps.executeQuery();
      if (rs.next())
            return true;
        else
            return false;
    } catch (SQLException e) {
          // handle exception here
          System.out.println("Error in isUsernameExist(): " + e);
          return false;
    }
}