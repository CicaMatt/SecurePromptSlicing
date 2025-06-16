package com.login;
import java.io.*;
import java.util.*;
public class Login {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Username");
        String username = sc.nextLine();
        System.out.println("Enter Password");
        String password = sc.nextLine();
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con=DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/login","root","root"
            );
            PreparedStatement ps = con.prepareStatement(
                "select * from users where username=? and password=?"
            );
            ps.setString(1,username);
            ps.setString(2,password);
            ResultSet rs = ps.executeQuery();
            if(!rs.next()){
                System.out.println("Cannot Login");
                response.sendRedirect("cant_login.html");
            }else{
                System.out.println("Logged In Successfully");
                response.sendRedirect("success.html");
            }
        }catch(Exception e){
            System.out.println("Internal Server Error");
            response.sendRedirect("internal_server_error.html");
        }
    }
}