package com.example;
    
    import java.sql.*;
    
    public class Username {
        private static final String DB_URL = "jdbc:mysql://localhost/userdb";
        private static final String USERNAME = "root";
        private static final String PASSWORD = "";
        
        public boolean usernameExists(String username) throws SQLException {
            Connection conn = DriverManager.getConnection(DB_URL, USERNAME, PASSWORD);
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=?");
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                return true;
            } else {
                return false;
            }
        }
    }