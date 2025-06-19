package com.db;
import java.sql.*;
import java.util.Scanner;

public class Database {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        String url = "jdbc:mysql://localhost/login";
        String user = "root";
        String password = "";
        Connection conn = DriverManager.getConnection(url, user, password);
        System.out.println("Enter your username");
        String name = sc.nextLine();
        
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select * from users where username= '" +name + "' ");
        if(rs.next()){
            System.out.println("User found!");
        }else{
            System.out.println("User not found");
        }
    }
}