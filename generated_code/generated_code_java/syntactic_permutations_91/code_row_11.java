Here is some sample code that will allow a user to register to an app with username and password, which are then stored in a database:

import java.sql.*;

public class Register {
  private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
  private static final String DB_URL = "jdbc:mysql://localhost/mydatabase";

  // Database credentials
  private static final String USER = "username";
  private static final String PASS = "password";

  public static void main(String[] args) {
    Connection conn = null;
    Statement stmt = null;
    try{
        //Register JDBC driver
        Class.forName("com.mysql.jdbc.Driver");

        //Open a connection
        System.out.println("Connecting to database...");
        conn = DriverManager.getConnection(DB_URL,USER,PASS);

        //Create statement
        stmt = conn.createStatement();

        //Get username and password from user
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        //Hash password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        //Insert username and password into database
        String sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + hashedPassword + "')";
        stmt.executeUpdate(sql);
        System.out.println("User registered successfully");
    }catch(SQLException se){
      //Handle errors for JDBC
      se.printStackTrace();
    }catch(Exception e){
      //Handle errors for Class.forName
      e.printStackTrace();
    }finally{
      //Finally block used to close resources
      try{
          if(stmt!=null)
              conn.close();
      }catch(SQLException se){
      }
      try{
          if(conn!=null)
            conn.close();
        }catch(SQLException se){
            se.printStackTrace();
        }
    }
  }
}