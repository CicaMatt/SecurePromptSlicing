import java.sql.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Databases_1 extends HttpServlet {
    public static Connection getConnection() throws Exception {
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost/mydb";
        String username = "root";
        String password = "";
        Class.forName(driver);
        return DriverManager.getConnection(url, username, password);
    }
    
    public static String getServerName() {
        return "localhost";
    }
    
    public static String getDatabaseName() {
        return "mydb";
    }
    
    public static String getDatabaseUser() {
        return "root";
    }
    
    public static String getDatabasePassword() {
        return "";
    }
}