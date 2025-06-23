package com.dv;
import java.sql.*;
public class Login{
    public static void main(String[] args) {
        String username = "username";
        String password = "password";
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con= DriverManager.getConnection("url","user","password");
            Statement statement = con.createStatement();
            ResultSet resultset =statement.executeQuery("select * from users where username='"+username+"'and password='"+password+"' ");
            if(resultset.next()){
                System.out.println("Login Successfully");
            }else{
                System.out.println("Please Try Again");
            }
        }catch(Exception e){
            System.out.println(e);
        }
    }
}