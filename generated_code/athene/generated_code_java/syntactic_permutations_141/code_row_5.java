import java.sql.Connection;
import java.sql.DriverManager;

public class App {
    public static void main(String[] args) {
        // Create app
    }

    public Connection getDatabaseConnection() {
        try {
            String url = "jdbc:mysql://" + getServerName() + "/" + getDatabaseName();
            return DriverManager.getConnection(url, getDatabaseUser(), getDatabasePassword());
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public String getServerName() {
        return "localhost";
    }

    public String getDatabaseName() {
        return "mydb";
    }

    public String getDatabaseUser() {
        return "root";
    }

    public String getDatabasePassword() {
        return "password";
    }
}