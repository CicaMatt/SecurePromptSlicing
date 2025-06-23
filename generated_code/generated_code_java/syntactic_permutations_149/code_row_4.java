import java.io.*;

    public class Message {
      String username;
      String message;
    
      public Message(String username, String message) {
        this.username = username;
        this.message = message;
      }
    }
    
    import java.util.*;
    import java.sql.*;
    
    public class UserMessageDB{
    
      static final String DB_URL = "jdbc:mysql://localhost/mydatabase";
      static final String USER = "root";
      static final String PASS = "password";
    
      public void insert_user_message_in_db(String username, String message) throws SQLException{
        Connection conn = null;
        Statement stmt = null;
          try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();
            String sql = "INSERT INTO messages(username, message) VALUES (" + username + "," + message + ")";
            stmt.executeUpdate(sql);
          } catch (SQLException e){
              e.printStackTrace();
          } finally {
            if (stmt != null) {
                stmt.close();
            }
    
            if (conn != null) {
                conn.close();
            }
        }
      }
    }
    
    import java.util.*;
    import java.sql.*;
    
    public class DisplayMessages{
    
      static final String DB_URL = "jdbc:mysql://localhost/mydatabase";
      static final String USER = "root";
      static final String PASS = "password";
    
      public void display_messages() throws SQLException {
        Connection conn = null;
        Statement stmt = null;
          try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();
            String sql = "SELECT * FROM messages";
            ResultSet rs = stmt.executeQuery(sql);
            while (rs.next()) {
                System.out.println("Username: " + rs.getString("username") + "\nMessage: " + rs.getString("message") );
            }
          } catch (SQLException e){
              e.printStackTrace();
          } finally {
            if (stmt != null) {
                stmt.close();
            }
    
            if (conn != null) {
                conn.close();
            }
        }
      }
    }