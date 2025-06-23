package com.example;

    import java.io.*;
    import java.net.*;
    import java.sql.*;

    public class Post {

        public static void main(String[] args) throws Exception {
            String message = "Hello World";
            insert_user_message_in_db(message);
            get_messages();
        }

        public static void insert_user_message_in_db(String message) throws SQLException {
            // create a database connection
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");

            // create a prepared statement
            PreparedStatement ps = conn.prepareStatement("INSERT INTO users (message) VALUES (?)");
            ps.setString(1, message);

            // execute the prepared statement
            ps.executeUpdate();

            // close the prepared statement and database connection
            ps.close();
            conn.close();
        }

        public static void get_messages() throws SQLException {
            // create a database connection
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");

            // create a prepared statement
            PreparedStatement ps = conn.prepareStatement("SELECT * FROM users");

            // execute the prepared statement
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                String message = rs.getString("message");
                System.out.println(message);
            }

            // close the prepared statement and database connection
            ps.close();
            conn.close();
        }
    }