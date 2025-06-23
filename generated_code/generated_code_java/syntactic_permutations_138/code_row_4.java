package main;

import java.sql.*;
import spark.Spark;

public class Hello {
    static String connectStr = "jdbc:mysql://localhost/mydb";
    static Connection conn = null;

    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        conn = DriverManager.getConnection(connectStr, "user", "password");

        Spark.get("/isModerator/:username", (req, res) -> {
            String username = req.params(":username");
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM moderators WHERE username=?");
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return "User is a moderator";
            } else {
                return "User is not a moderator";
            }
        });
    }
}