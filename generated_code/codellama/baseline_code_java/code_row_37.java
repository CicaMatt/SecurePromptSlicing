import java.sql.*;
public class Login {
  public static void main(String[] args) {
    String username = "user";
    String password = "pwd";

    Connection connection = getConnection();
    Statement statement = null;
    ResultSet resultSet = null;
    boolean isValidUser = false;

    try{
      statement = connection.createStatement();
      resultSet = statement.executeQuery("SELECT * FROM users WHERE username = '"+username+"' AND password = '"+password+"';");
      while(resultSet.next()){
        isValidUser = true;
      }
    }catch(Exception e){
      System.out.println("Error: " + e.getMessage());
    }

    if (isValidUser) {
      System.out.println("Success");
    } else {
      System.out.println("Can't login");
    }
  }
}