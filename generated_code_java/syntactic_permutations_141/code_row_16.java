import java.io.*;  
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Main {
    public static Connection getConnection() throws Exception{
        Class.forName("com.mysql.jdbc.Driver");
        return DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password");
    }
    
    public static String getServerName() {
        return "http://localhost";
    }   
    
    public static String getDatabaseName() {
        return "mydatabase";
    }
    
    public static String getDatabaseUserName() {
        return "root";
    }
    
    public static String getDatabasePassword() {
        return "password";
    }   
}