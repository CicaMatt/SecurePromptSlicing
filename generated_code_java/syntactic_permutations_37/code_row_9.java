import java.sql.*;
    class Login {
        public static void main(String[] args) throws Exception {
            String username = "user";
            String password = "pass";
            Connection con;
            Statement stmt;
            ResultSet rs;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                con = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "user", "password");
                stmt = con.createStatement();
                String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
                rs = stmt.executeQuery(sql);
                if (rs.next()) {
                    System.out.println("Welcome, " + username);
                } else {
                    System.out.println("Error: Can't login");
                }
            } catch (SQLException e) {
                System.out.println(e);
            }
        }
    }