import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/database")
public class DatabaseApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "myuser";
    private static final String PASS = "mypassword";

    @GET
    @Path("/connect")
    @Produces(MediaType.APPLICATION_JSON)
    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    @GET
    @Path("/serverName")
    @Produces(MediaType.TEXT_PLAIN)
    public String getServerName() {
        return "localhost";
    }

    @GET
    @Path("/databaseName")
    @Produces(MediaType.TEXT_PLAIN)
    public String getDatabaseName() {
        return "mydatabase";
    }

    @GET
    @Path("/databaseUser")
    @Produces(MediaType.TEXT_PLAIN)
    public String getDatabaseUser() {
        return USER;
    }

    @GET
    @Path("/databasePassword")
    @Produces(MediaType.TEXT_PLAIN)
    public String getDatabasePassword() {
        return PASS;
    }
}