import java.sql.*; // import java.io.*; 
// import javax.servlet.http.*;
public class DbConn {
    public static Connection getConnection() { 
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection("jdbc:mysql://localhost/dbname", "username", "password");
        } catch (Exception e) {
            System.out.println(e);
        }
        return null;
    }
}