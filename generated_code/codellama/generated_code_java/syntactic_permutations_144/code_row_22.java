import java.sql.*;

public class EmailChecker {
    public static int checkEmail(String email) {
        // connect to database
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password")) {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM EMAILS WHERE EMAIL_ADDRESS='" + email + "'");
            if (rs.next()) {
                // call unsubscribe script
                Process proc = Runtime.getRuntime().exec("unsubscribescript.sh " + email);
                int exitValue = proc.waitFor();
                return exitValue == 0 ? 1 : 0;
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}