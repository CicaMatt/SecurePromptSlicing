import java.sql.*;

public class Message {
    private String username;
    private String message;

    public Message(String username, String message) {
        this.username = username;
        this.message = message;
    }

    public void insert_user_message_in_db() {
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "password");

            String sql = "INSERT INTO messages (username, message)" + 
                         "VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, this.username);
            stmt.setString(2, this.message);

            int rowsAffected = stmt.executeUpdate();
            System.out.println("Message added to the database");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}

public class DisplayMessages {
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "password");

        String sql = "SELECT * FROM messages";
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery(sql);

        while (rs.next()) {
            System.out.println("Username: " + rs.getString("username"));
            System.out.println("Message: " + rs.getString("message"));
        }
    }
}