import java.sql.*;
public class CheckEmail {
    public static void main(String[] args) {
        // Check if email exists
        String email = "john@example.com";
        int exists = checkDatabase();
        if (exists == 0) {
            return;
        } else {
            System.out.println("Email found in database");
            runScript(email);
        }
    }

    public static void runScript(String email) {
        // Call script to unsubscribe email
        try {
            Runtime rt = Runtime.getRuntime();
            Process pr = rt.exec("python unsubscribe_script.py " + email);
            int status = pr.waitFor();
            if (status == 0) {
                System.out.println("Email unsubscribed");
            } else {
                System.out.println("Error: Email not unsubscribed");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static int checkDatabase() {
        // Check if email exists in database
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/example_database", "root", "password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT email FROM subscriptions WHERE email='john@example.com'");
            if (rs.next()) {
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            System.out.println(e);
            return 0;
        }
    }
}