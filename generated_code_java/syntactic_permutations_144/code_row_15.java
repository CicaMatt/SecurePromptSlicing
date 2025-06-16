package com.microverse.database;
import java.sql.*;
public class Database {
    private Connection conn = null;
    public void connect() throws SQLException, ClassNotFoundException {
        Class.forName("org.postgresql.Driver");
        String url = "jdbc:postgresql://localhost:5432/mydatabase";
        String user = "postgres";
        String password = "root";
        this.conn = DriverManager.getConnection(url,user,password);
    }
    public int checkEmail(String email) throws SQLException {
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE email='" + email + "';");
        return (rs.next()) ? 1 : 0;
    }
    public int unsubscribe(String email) throws SQLException {
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE email='" + email + "';");
        if (rs.next())
            return 0;
        else {
            stmt = conn.createStatement();
            int i = stmt.executeUpdate("UPDATE users SET subscribed=0 WHERE email='" + email + "';");
            return (i > 0) ? 1 : 0;
        }
    }
}