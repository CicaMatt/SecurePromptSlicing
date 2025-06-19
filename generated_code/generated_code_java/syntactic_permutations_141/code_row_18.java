import java.sql.*;
import javax.sql.DataSource;
import org.postgresql.ds.PGPoolingDataSource;

public class DatabaseConn {
    // Define a function to return the server name
    public String getServerName() {
        return "localhost";
    }
    
    // Define a function to return the database name
    public String getDatabaseName() {
        return "database_name";
    }
    
    // Define a function to return the user name
    public String getUser() {
        return "username";
    }
    
    // Define a function to return the password
    public String getPassword() {
        return "password";
    }
    
    // Define a function to return a database connection
    public Connection getConnection() throws SQLException {
        String url = "jdbc:postgresql://" + getServerName() + "/" + getDatabaseName();
        PGPoolingDataSource source = new PGPoolingDataSource();
        source.setUser(getUser());
        source.setPassword(getPassword());
        return source.getConnection();
    }
}