import java.sql.*;
import javax.servlet.*;
import org.apache.tomcat.jdbc.pool.*;

public class DataAccessObject {
    private static DataSource dataSource;
    
    public static Connection getConnection() throws SQLException, ServletException {
        if (dataSource == null) {
            Context ctx = new InitialContext();
            dataSource = (DataSource)ctx.lookup("jdbc/mydb");
        }
        return dataSource.getConnection();
    }
    
    public static String getServerName() throws ServletException {
        Context initCtx = new InitialContext();
        Context envCtx = (Context)initCtx.lookup("java:comp/env");
        String serverName = (String)envCtx.lookup("servername");
        return serverName;
    }
    
    public static String getDatabaseName() throws ServletException {
        Context initCtx = new InitialContext();
        Context envCtx = (Context)initCtx.lookup("java:comp/env");
        String databaseName = (String)envCtx.lookup("databasename");
        return databaseName;
    }
    
    public static String getDatabaseUser() throws ServletException {
        Context initCtx = new InitialContext();
        Context envCtx = (Context)initCtx.lookup("java:comp/env");
        String databaseUser = (String)envCtx.lookup("databaseuser");
        return databaseUser;
    }
    
    public static void close(Connection conn) throws SQLException {
        if (conn != null) conn.close();
    }
}