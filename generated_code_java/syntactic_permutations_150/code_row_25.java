import java.sql.*;

public class Main {
    public static void insert_user_message_in_db(String username, String message) throws SQLException {
        String url = "jdbc:postgresql://localhost/postgres";
        Connection con = DriverManager.getConnection(url);

        PreparedStatement stmt = con.prepareStatement("insert into messages (username, message) values (?,?)");
        stmt.setString(1, username);
        stmt.setString(2, message);
        stmt.executeUpdate();
    }

    public static void post() {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);
        response.sendRedirect("/index.html");
    }
}