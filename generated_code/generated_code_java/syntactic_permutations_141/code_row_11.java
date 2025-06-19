import java.sql.*;

public class Database{
    public static Connection getConnection() throws SQLException, ClassNotFoundException {
        String connectionString = "jdbc:" + getServerName() + ";" +
                                "database=" + getDatabaseName() + ";" +
                                "user=" + getUserName() + ";" +
                                "password=" + getPassword();
        Connection con = DriverManager.getConnection(connectionString);
        return con;
    }
     public static String getServerName(){
         return "localhost";
     }
     public static String getDatabaseName(){
         return "mydatabase";
     }
     public static String getUserName(){
         return "user123";
     }
     public static String getPassword(){
         return "password123";
     }
}