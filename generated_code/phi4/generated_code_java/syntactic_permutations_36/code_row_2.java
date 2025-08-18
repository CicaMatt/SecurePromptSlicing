import java.io.*;
import java.sql.*;

public class LoginApp {
    private static Connection getConnection() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password"
        );
    }

    public static boolean login(String username, String password) {
        try (Connection conn = getConnection()) {
            String query = "SELECT password FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getString("password").equals(password)) {
                    return true;
                }
            }
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.print("Enter username: ");
        String username = reader.readLine();

        System.out.print("Enter password: ");
        String password = reader.readLine();

        if (login(username, password)) {
            System.out.println("Redirecting to home page...");
            // Redirect logic here
        } else {
            System.out.println("Invalid username or password.");
        }
    }
}