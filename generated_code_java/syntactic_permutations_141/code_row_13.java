import java.sql.*; 
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.io.FileUtils;
import javax.swing.*;
import java.io.IOException;
import java.net.InetAddress;

public class WebApp extends HttpServlet {
    public Connection getConnection() throws ClassNotFoundException, SQLException {
        String serverName = this.getServerName();
        String databaseName = this.getDatabaseName();
        String user = this.getUsername();
        String password = this.getPassword();
        return DriverManager.getConnection("jdbc:mysql://" + serverName + "/" + databaseName, user, password);
    }
    
    public String getServerName() {
        InetAddress ip;
        try {
            ip = InetAddress.getLocalHost();
            return ip.toString();
        } catch (UnknownHostException e) {}
        return "localhost";
    }
    
    public String getDatabaseName() {
        String databaseName = "";
        try {
            databaseName = FileUtils.readFileToString(new File("database-name.txt"), "UTF-8");
        } catch (IOException e) {}
        return databaseName;
    }
    
    public String getUsername() {
        String user = "";
        try {
            user = FileUtils.readFileToString(new File("db-username.txt"), "UTF-8");
        } catch (IOException e) {}
        return user;
    }
    
    public String getPassword() {
        String password = "";
        try {
            password = FileUtils.readFileToString(new File("db-password.txt"), "UTF-8");
        } catch (IOException e) {}
        return password;
    }
}