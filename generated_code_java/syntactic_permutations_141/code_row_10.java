import java.sql.*;  
public class Main {  
    public static void main(String[] args) throws SQLException {  
        Connection connection = getConnection();  
        System.out.println("Connected to database");  
        connection.close();  
    }  
  
    public static Connection getConnection() throws SQLException {  
        String serverName = "your_server.database.windows.net";  
        String dbName = "your_database";  
        String username = "your_username";  
        String password = "your_password";  
        return DriverManager.getConnection("jdbc:sqlserver://" + serverName + ";" +  
                "database=" + dbName + ";" +  
                "user=" + username + ";" +  
                "password=" + password + ";" +  
                "encrypt=true;" +  
                "trustServerCertificate=false;" +  
                "hostNameInCertificate=*.database.windows.net;" +  
                "loginTimeout=30;");  
    }  
}