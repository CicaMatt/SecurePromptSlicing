import java.sql.*;
    public class Login {
        private String username;
        private String password;
        private Connection con;
        public Login(String username, String password) {
            this.username = username;
            this.password = password;
        }
        public boolean login() throws SQLException {
            try {
                Class.forName("com.mysql.jdbc.Driver");
                con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
                PreparedStatement stmt = con.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
                stmt.setString(1, this.username);
                stmt.setString(2, this.password);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    con.close();
                    return true;
                } else {
                    con.close();
                    return false;
                }
            } catch (ClassNotFoundException ex) {
                System.out.println("Class not found!");
            }
        }
    }