import java.sql.*;
    
    public class LoginPage {
      private String username;
      private String password;
    
      //getters and setters
    
      private boolean checkLogin(){
        Connection conn = null;
        Statement stmt = null;
        try{
          Class.forName("com.mysql.jdbc.Driver");
          conn = DriverManager.getConnection(DB_URL, USER, PASS);
          String sql = "SELECT * FROM users WHERE username='" + this.username + "' AND password='" + this.password + "';";
          stmt = conn.createStatement();
          ResultSet rs = stmt.executeQuery(sql);
    
          if (rs.next()){
            return true;
          } else {
            return false;
          }
        } catch (SQLException e) {
          System.out.println("Error in checking login");
          e.printStackTrace();
          return false;
        } finally{
          try {
            stmt.close();
            conn.close();
          } catch (SQLException e){
            System.out.println("Error while closing connection");
            e.printStackTrace();
          }
        }
      }
    
      private void login(){
        if(checkLogin()){
          //redirect to dashboard page
        } else {
          //redirect back to login page
        }
      }
    }