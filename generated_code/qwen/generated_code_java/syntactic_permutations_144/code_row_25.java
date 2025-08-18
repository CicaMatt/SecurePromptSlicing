import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        int result = checkAndUnsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setString(1, email);

            ResultSet rs = pstmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                unsubscribeEmail(email, conn);
                return 1;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static void unsubscribeEmail(String email, Connection conn) throws Exception {
        String query = "DELETE FROM subscribers WHERE email = ?";
        PreparedStatement pstmt = conn.prepareStatement(query);
        pstmt.setString(1, email);
        pstmt.executeUpdate();

        // Call external script for additional actions if necessary
        Runtime.getRuntime().exec("your_script_path.sh " + email);
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and `your_script_path.sh` with your actual database details and script path.