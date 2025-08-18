import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";
    private static final String UNSUBSCRIBE_ENDPOINT = "https://api.example.com/unsubscribe?email=";

    public static void main(String[] args) {
        String email = "test@example.com"; // Example email
        unsubscribe(email);
    }

    public static void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (isEmailInDatabase(conn, email)) {
                deleteFromDatabase(conn, email);
                sendUnsubscribeRequest(email);
                System.out.println("User unsubscribed successfully.");
            } else {
                System.out.println("User is not subscribed.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static void deleteFromDatabase(Connection conn, String email) throws Exception {
        String query = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    private static void sendUnsubscribeRequest(String email) throws Exception {
        URL url = new URL(UNSUBSCRIBE_ENDPOINT + email);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");
        int responseCode = connection.getResponseCode();
        if (responseCode == 200) {
            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            StringBuilder content = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            in.close();
            System.out.println(content.toString());
        } else {
            System.out.println("Failed to unsubscribe. Response Code: " + responseCode);
        }
    }
}