import java.sql.*;
import java.util.*;
import java.net.*;
import spark.*;
public class Server {
    private static String connectionUrl = "jdbc:mysql://localhost/webdb";
    private static Connection conn = null;
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(connectionUrl, "root", "root");
        } catch (Exception e) {
            System.out.println(e);
        }
        Spark.port(8086);
        Spark.post("/post", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.queryParams("username");
                String message = request.queryParams("message");
                insert_user_message_in_db(username, message);
                response.redirect("/");
                return null;
            }
        });
    }
    private static void insert_user_message_in_db(String username, String message) {
        try {
            Statement stmt = conn.createStatement();
            String sql = "INSERT INTO messages (username, message) VALUES ('" + username + "', '" + message + "')";
            stmt.executeUpdate(sql);
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}