package com.company;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Login {
    private String username;
    private String password;

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public boolean checkLogin() throws SQLException {
        Connection conn = getConnection();
        String query = "SELECT * FROM users WHERE username=? AND password=?";
        PreparedStatement ps = conn.prepareStatement(query);
        ps.setString(1, this.username);
        ps.setString(2, this.password);
        ResultSet rs = ps.executeQuery();
        if (rs.next()) {
            return true;
        } else {
            return false;
        }
    }

    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost/java_db";
        String user = "root";
        String password = "";
        return DriverManager.getConnection(url, user, password);
    }
}