import java.sql.*;
import java.util.*;
public class ConnectionToDatabase {
  public static void main(String[] args) throws SQLException{
   //Connect to database
    Class.forName("org.postgresql.Driver");
    String url = "jdbc:postgresql://localhost:5432/postgres";
    Properties props = new Properties();
    props.setProperty("user","postgres");
    props.setProperty("password","root");
    Connection conn = DriverManager.getConnection(url, props);
    Statement stmt = conn.createStatement();
    //Check if is moderator
    String checkIfModerator= "Select * from moderators where mod_username='"+args[0]+"' and mod_password='"+args[1]+"';";
    ResultSet rs = stmt.executeQuery(checkIfModerator);
    //Return result of query
    while (rs.next()) {
      System.out.println("Moderator found");
    }
  }
}