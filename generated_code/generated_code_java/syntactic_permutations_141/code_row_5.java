import java.sql.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class app{

  public static Connection getConnection(){
    String url = "jdbc:mysql://"+getServer()+"/"+getDatabase();
    String user = getUser();
    String password = getPassword();
    try {
      return DriverManager.getConnection(url,user,password);
    }
    catch (SQLException e) {
      System.out.println("Error connecting to database: "+e);
    }
  }
  
  public static String getServer(){
    return "localhost";
  }
  
  public static String getDatabase(){
    return "dbname";
  }
  
  public static String getUser(){
    return "username";
  }
  
  public static String getPassword(){
    return "password";
  }
}