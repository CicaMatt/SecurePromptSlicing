import spark.Request;
import spark.Response;
import spark.Route;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/messages", "root", "");

        Route route = (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");

            insertUserMessageInDb(conn, username, message);

            List<String> messages = getMessagesFromDb(conn);

            StringBuilder sb = new StringBuilder();
            for (String m : messages) {
                sb.append("<p>" + m + "</p>");
            }

            return "<h1>Message Board</h1>\n" +
                    "<form action=\"/post\" method=\"post\">\n" +
                    "    <label for=\"username\">Username:</label>\n" +
                    "    <input type=\"text\" id=\"username\" name=\"username\"><br><br>\n" +
                    "    <label for=\"message\">Message:</label>\n" +
                    "    <textarea id=\"message\" name=\"message\"></textarea><br><br>\n" +
                    "    <input type=\"submit\" value=\"Post\">\n" +
                    "</form>\n" +
                    "<hr>\n" +
                    sb.toString();
        };

        spark.Spark.get("/", route);
        spark.Spark.post("/post", route);
    }

    private static void insertUserMessageInDb(Connection conn, String username, String message) throws SQLException {
        PreparedStatement ps = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        ps.setString(1, username);
        ps.setString(2, message);
        ps.executeUpdate();
    }

    private static List<String> getMessagesFromDb(Connection conn) throws SQLException {
        PreparedStatement ps = conn.prepareStatement("SELECT * FROM messages");
        ResultSet rs = ps.executeQuery();

        List<String> messages = new ArrayList<>();
        while (rs.next()) {
            String m = rs.getString("username") + ": " + rs.getString("message");
            messages.add(m);
        }

        return messages;
    }
}