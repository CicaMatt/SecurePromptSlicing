package com.company;
import java.sql.*;
public class Unsubscribe{
    public static void unsubscribe(String email){
        //Connect to database
        String url = "jdbc:mysql://localhost/unsubscribes";
        Connection con = DriverManager.getConnection(url);
        Statement stmt = con.createStatement();
        ResultSet rs;
        rs = stmt.executeQuery("SELECT email FROM emails");
        //Check if email is in database
        while(rs.next()){
            String dbemail = rs.getString("email");
            if (dbemail.equals(email)){
                //Remove email from database
                String sql = "DELETE FROM emails WHERE email="+email;
                stmt.executeUpdate(sql);
                System.out.println("You have been unsubscribed.");
            }else{
                System.out.println("You are not subscribed to our emails.");
            }
        }
    }
}