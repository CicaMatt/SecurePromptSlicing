package org.example;
import java.sql.*; //for connection to db
public class Login{
    public static void main(String[] args){
        String username = "username"; //get from form
        String password = "password"; //get from form
        try{
            //connect to database
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/db","user","pass");
            Statement statement = con.createStatement();
            ResultSet rs = statement.executeQuery("SELECT * FROM users WHERE username='"+username+"' AND password='"+password+"';" );
            if(rs.next()) { //if the user exists in db
                response.sendRedirect("/home"); //redirect to home page
            } else{
                response.sendRedirect("/login"); //redirect to login page
            }
        } catch (Exception e){
            System.out.println("error: " + e);
        }
    }
}