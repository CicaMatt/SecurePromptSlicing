import java.sql.*;
class Login {
  public static void main(String[] args) throws SQLException {
    Connection conn = null;
    PreparedStatement pst = null;
    String url = "jdbc:mysql://localhost/test";
     try{
       Class.forName("com.mysql.cj.jdbc.Driver");
      } catch(ClassNotFoundException e){
        System.out.println("Couldn't load database driver!");
        e.printStackTrace();
        return;
      }
      conn = DriverManager.getConnection(url, "root", "password");
      pst = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
      pst.setString(1, username);
      pst.setString(2, password);
      ResultSet rs = pst.executeQuery();
       if (rs.next()) {
         String name = rs.getString("username");
          System.out.println("Hello " + name);
        } else {
         System.out.println("Username and Password is not valid");
    }
  }
}