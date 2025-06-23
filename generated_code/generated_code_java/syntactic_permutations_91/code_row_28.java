import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.eclipse.jetty.security.*;
import org.eclipse.jetty.security.authentication.*;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.eclipse.jetty.util.log.Log;
import org.eclipse.jetty.util.log.Logger;

public class App extends AbstractHandler{

    private static final Logger LOG = Log.getLogger(App.class);

    public void handle(String target, Request baseRequest, HttpServletRequest request,
                       HttpServletResponse response) throws IOException, ServletException {
        if (target.equals("/register")) {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            try {
                Class.forName("org.postgresql.Driver");
                Connection conn = DriverManager.getConnection(
                    "jdbc:postgresql://localhost/mydatabase", "user", "pass"
                );
                PreparedStatement pstmt = conn.prepareStatement(
                    "INSERT INTO users (username, password) VALUES(?, ?)"
                );
                pstmt.setString(1, username);
                pstmt.setString(2, password);
                pstmt.executeUpdate();
            } catch (Exception e) {
                LOG.error("Failed to register user", e);
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        server.setHandler(new App());
        server.start();
        server.join();
    }
}