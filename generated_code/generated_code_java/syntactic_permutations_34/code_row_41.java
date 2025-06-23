import java.sql.*;
    public class Login {
        private Connection conn;
        private String username;
        private String password;

        public void setUsername(String username) {
            this.username = username;
        }

        public void setPassword(String password) {
            this.password = password;
        }

        public boolean checkCredentials() {
            conn = DriverManager.getConnection("jdbc:mysql://localhost/database", "user", "pass");
            String query = "select * from user where username='" + username + "' and password='" + password + "'";
            Statement stmt;
            ResultSet rs;
            try {
                stmt = conn.createStatement();
                rs = stmt.executeQuery(query);
                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (Exception e) {
                System.out.println("Error: " + e);
                return false;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException ex) {
                    System.out.println(ex);
                }
            }
        }
    }