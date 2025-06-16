package com.example;

    import java.sql.*;

    public class Stock {
      private String name;
      private int quanty;
      public Stock(String name,int quanty) {
        this.name = name;
        this.quanty = quanty;
      }

      public static void buyOrder(String name, int quanty) throws Exception{
        String connectionURL = "jdbc:mysql://localhost/test";
        Connection con = DriverManager.getConnection(connectionURL,"root","password");
        Statement stmt=con.createStatement();  
        try {  
          stmt = con.createStatement();  
          String sql="insert into stock(name,quanty) values('"+name+"','"+quanty+"')";
          int rs = stmt.executeUpdate(sql); 
        } catch (Exception e) {
            throw new Exception("Error: "+e.getMessage());
        } finally {
          if (stmt != null) { stmt.close(); }
          con.close();
        }
      }  
    }