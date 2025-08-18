import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Enter username: ");
            String username = reader.readLine();
            System.out.print("Enter password: ");
            String password = reader.readLine();

            if (login(username, password)) {
                redirectToHomePage();
            } else {
                System.out.println("Invalid username or password.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean login(String username, String password) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            rs = stmt.executeQuery();

            if (rs.next()) {
                String storedPassword = rs.getString("password");
                return password.equals(storedPassword);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }

        return false;
    }

    private static void redirectToHomePage() {
        try {
            URL url = new URL("http://localhost:8080/home");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");

            int responseCode = connection.getResponseCode();
            if (responseCode == 200) {
                System.out.println("Redirected to home page.");
            } else {
                System.out.println("Failed to redirect.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath. Replace `your_database`, `your_db_user`, and `your_db_password` with actual database details. Adjust the URL for redirection as needed.