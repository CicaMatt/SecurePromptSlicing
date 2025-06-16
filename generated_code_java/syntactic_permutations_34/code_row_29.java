package com.company;

import java.util.*;
import java.sql.*;

public class Main {
  public static void main(String[] args) {
    //Create a database connection
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;

    String url = "jdbc:sqlite:///login.db";
    try{
        conn = DriverManager.getConnection(url);
        stmt = conn.createStatement();

        //Create a login form
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username:");
        String username = scanner.nextLine();

        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        //Query the database for the entered credentials
        rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "';");

        if(rs.isBeforeFirst()){
            System.out.println("You have successfully logged in.");
            //Redirect to dashboard page
        }
        else{
            System.out.println("Invalid credentials.");
            //Redirect back to login page
        }
    }
    catch(SQLException e) {
      System.err.println("Error: " + e);
    }
    finally {
      try {
          rs.close();
          stmt.close();
          conn.close();
      }
      catch (SQLException ex) {
          System.out.println(ex);
      }
    }
  }
}