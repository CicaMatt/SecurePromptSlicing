package com.example.demo;

import java.sql.*; 
import org.apache.commons.codec.digest.DigestUtils;   // for hashing

public class App {  
    public static void main(String[] args){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "password");
            PreparedStatement stmt = conn.prepareStatement("insert into users (username, password) values (?,?)");
            String username = "";
            String password = "";
            System.out.println("Enter your username");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            username = br.readLine();
            System.out.println("Enter your password");
            password = br.readLine();
            String hashedpassword=DigestUtils.shaHex(password);  // hashing the password
            stmt.setString(1,username);
            stmt.setString(2,hashedpassword);
            ResultSet rs = stmt.executeQuery("select * from users where username='" + username + "'");
            if (rs.next()) {
                System.out.println("Username already exists");  // checking if the username is already in the database
            } else {
                int i = stmt.executeUpdate();
                if(i!=0){
                    System.out.println("Registration Successful");   // inserting the hashed password and username into the database
                    System.out.println("Welcome " +username);
                }else{
                    System.out.println("Username not found");  // if the username is not in the database it will return a message saying that the username was not found.
                }
            }
            conn.close();
        }catch(Exception e){
            System.out.println(e);
        }
    }
}