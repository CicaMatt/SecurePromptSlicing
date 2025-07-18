package com.example.demo;

    import java.io.IOException;
    import java.sql.*;
    import java.util.HashMap;
    import java.util.Map;
    import java.util.Properties;

    public class Moderator {
        
        private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        private static final String DB_URL = "jdbc:mysql://localhost/mydatabase";

        //  Database credentials
        private static final String USER = "root";
        private static final String PASS = "password";
    
        public Map<String, Object> isModerator(int userId) {
            Connection conn = null;
            PreparedStatement stmt = null;
            ResultSet rs = null;

            try {
                // Register JDBC driver
                Class.forName(JDBC_DRIVER);

                // Open a connection
                conn = DriverManager.getConnection(DB_URL, USER, PASS);

                // SQL query command
                String sql = "SELECT isModerator FROM users WHERE userId=?";

                stmt = conn.prepareStatement(sql);
                stmt.setInt(1, userId);
                rs = stmt.executeQuery();

                Map<String, Object> map = new HashMap<>();
                if (rs.next()) {
                    map.put("isModerator", rs.getBoolean("isModerator"));
                } else {
                    map.put("isModerator", false);
                }

                return map;
            } catch (SQLException se) {
                // Handle errors for JDBC
                Map<String, Object> map = new HashMap<>();
                map.put("isModerator", false);

                return map;
            } catch (ClassNotFoundException e) {
                Map<String, Object> map = new HashMap<>();
                map.put("isModerator", false);

                return map;
            } finally {
                // Finally block used to close resources
                try {
                    if (stmt != null) {
                        stmt.close();
                    }
                } catch (SQLException se2) {
                    Map<String, Object> map = new HashMap<>();
                    map.put("isModerator", false);

                    return map;
                } // do nothing 
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException se) {
                    Map<String, Object> map = new HashMap<>();
                    map.put("isModerator", false);

                    return map;
                } // end finally try
            }
        }
    }