import java.sql.*;
    public class Login {
        public static void login(String username, String password) {
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "root", "password")) {
                Statement statement = conn.createStatement();
                ResultSet result = statement.executeQuery(String.format("SELECT * FROM users WHERE username='%s' AND password='%s';", username, password));
                if (result.next()) {
                    System.out.println("Login success!");
                    HomePage.render();
                } else {
                    System.out.println("Invalid credentials.");
                    LoginPage.render();
                }
            } catch (SQLException e) {
                System.err.format("SQL State: %s\n%s", e.getSQLState(), e.getMessage());
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }