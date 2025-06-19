import java.sql.*;
import java.util.Scanner;
class Unsubscribe {
    public static int checkSubscription(String userId) {
        // Check if exists in the database
        boolean isSubscribed = true;
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase", "root", "password");
            String query = "SELECT * FROM subscription WHERE id = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();
            if (!rs.next()) {
                isSubscribed = false;
            }
        } catch (SQLException e) {
            System.out.println("Error checking subscription: " + e.getMessage());
        }
        return isSubscribed ? unsubscribe(userId) : 0;
    }
    
    public static int unsubscribe(String userId) {
        // Call a script that unsubscribes the user
        try {
            Runtime rt = Runtime.getRuntime();
            Process pr = rt.exec("unsubscribe.sh " + userId);
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(pr.getInputStream()));
            return Integer.parseInt(stdInput.readLine());
        } catch (IOException e) {
            System.out.println("Error unsubscribing: " + e.getMessage());
        }
        return 0;
    }
}