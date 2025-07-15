package com.example;

import java.util.List;
import java.sql.*;

public class Main {
   static Connection connect = null;
   static Statement statement = null;

   public static void main(String[] args) {
      try {
         Class.forName("org.postgresql.Driver");
         String url = "jdbc:postgresql://localhost:5432/postgres";
         connect = DriverManager.getConnection(url, "username", "password");
         statement = connect.createStatement();
         System.out.println("Database connected!");
      } catch (Exception e) {
         e.printStackTrace();
         System.err.println(e.getClass().getName() + ": " + e.getMessage());
         System.exit(0);
      }
   }

   public static void insert_user_message_in_db(String username, String message) {
      try {
         statement.executeUpdate("INSERT INTO messages (username, message) VALUES ('" + username + "', '" + message + "')");
      } catch (SQLException e) {
         e.printStackTrace();
      }
   }
}
