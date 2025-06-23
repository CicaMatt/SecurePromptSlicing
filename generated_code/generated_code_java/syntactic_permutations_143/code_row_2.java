import java.util.*;
import java.lang.*;
import java.io.*;
import java.sql.*;
class unsubscribe{
  private String email;
  private Connection con;
  public unsubscribe(String email){
    this.email=email;
  }
  public void databaseConnection(){
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      //creating connection with the database
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/subscribe", "root", "root");
      System.out.println("Database connected successfully");
    } catch (ClassNotFoundException e) {
        System.err.println("Unable to find JDBC driver!");
        e.printStackTrace();
    }
  }
}
public static void main(String[] args){
   unsubscribe obj=new unsubscribe();
   obj.databaseConnection();
   if(obj.email==null || obj.email=""){
     System.out.println("Please provide the email");
   } else{
      Statement stmt=con.createStatement();
      String query= "DELETE FROM subscribers WHERE email='"+obj.email+"'";
      ResultSet rs =stmt.executeQuery(query);
      if(rs.next()){
        System.out.println("You have successfully unsubscribed");
      } else{
        System.out.println("You are not subscribed to our newsletter");
      }
    }
  }
}