import java.io.*;
import java.util.*;
import java.net.*;
import java.sql.*;

public class UserLogin{
    public static void main(String[] args) throws IOException, SQLException {
        //Inputs from user
        String username = "user";
        String password = "password";
        
        //Login Function
        if (login(username, password)) {
            System.out.println("Logged In Successfully");
        } else {
            System.out.println("Invalid Password!");
        }
    }
    
    public static boolean login(String username, String password) throws IOException, SQLException{
        //Creating Database Connection
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "password");
        
        //Preparing Prepared Statement
        PreparedStatement stmt = con.prepareStatement("SELECT username, password FROM login WHERE username=? AND password=?");
        stmt.setString(1, username);
        stmt.setString(2, password);
        
        //Executing Query and Storing Result
        ResultSet rs = stmt.executeQuery();
        
        //Checking if Username Exists in Database
        boolean exists = false;
        while (rs.next()) {
            String dbusername = rs.getString("username");
            String dbpassword = rs.getString("password");
            if(username.equals(dbusername) && password.equals(dbpassword)){
                exists = true;
            }
        }
        
        //Closing Connection and Returning Result
        con.close();
        return exists;
    }
}