import java.sql.*;  
import javax.naming.InitialContext;  
import javax.servlet.http.*;  
import javax.servlet.*;
import java.io.*;
import java.util.*;
public class WebApp extends HttpServlet {
    private Connection conn = null;
    private Statement stmt = null;
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String serverName = getServerName();
        String databaseName = getDatabaseName();
        String user = getUser();
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(serverName + databaseName, user);
            stmt = conn.createStatement();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public String getServerName() {
        return "jdbc:mysql://localhost/";
    }
    public String getDatabaseName() {
        return "?useSSL=false";
    }
    public String getUser() {
        return "root";
    }
}