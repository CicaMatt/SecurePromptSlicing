package org.example;
import java.sql.*;
public class Main {
  public static void main(String[] args) throws Exception{
   Class.forName("com.mysql.jdbc.Driver");
   Connection con= DriverManager.getConnection(
    "jdbc:mysql://localhost:3306/","root","password");
   Statement stmt=con.createStatement();
   String str="insert into stock values('"+name+"','"+quantity+"')";
   int x=stmt.executeUpdate(str);
  }
}