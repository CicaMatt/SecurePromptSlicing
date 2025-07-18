package com.moringaschool.registration;

import java.security.MessageDigest;
import java.sql.*;

public class Registration {
    
    public static void main(String[] args) throws SQLException, Exception { 		
        String url = "jdbc:mysql://localhost/registration";
        Connection connection = DriverManager.getConnection(url,"root","");
        PreparedStatement preparedstatement=connection.prepareStatement("insert into user (username,password,first_name,last_name,email) values(?,?,?,?,?)");
        MessageDigest messageDigest=MessageDigest.getInstance("MD5");
        String password = "123456789";
        String username="moringa";
        String first_name="Kiprotich";
        String last_name="Melvin";
        String email="kiprotich@gmail.com";
        messageDigest.update(password.getBytes());
        byte[] digest = messageDigest.digest();
        String myHash=String.format("%032x", new BigInteger(1,digest));
        preparedstatement.setString(1,username);
        preparedstatement.setString(2,myHash);
        preparedstatement.setString(3,first_name); 
        preparedstatement.setString(4,last_name);
        preparedstatement.setString(5,email);
        int row=preparedstatement.executeUpdate();
        if (row>0){
            System.out.println("Registration Successful");
        }else{
            System.out.println("Registration Failed");	
        }
    }
}