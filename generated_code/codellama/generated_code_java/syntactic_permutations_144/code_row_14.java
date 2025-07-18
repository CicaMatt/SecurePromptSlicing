import java.sql.*;

public class Unsubscribe {
    public static void main(String[] args) {
        String email = "test@email.com"; // example email
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "username", "password");
             Statement stmt = conn.createStatement();) {
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE email='" + email + "'");
            if (rs.next()) { // check if the email exists in the database
                String unsubscribeScriptPath = "/path/to/unsubscribe/script";
                Runtime runtime = Runtime.getRuntime();
                try {
                    Process process = runtime.exec(new String[]{"sh", unsubscribeScriptPath, "-email", email});
                    // wait for the script to finish running before continuing
                    int exitCode = process.waitFor();
                    if (exitCode == 0) {
                        System.out.println("1"); // script ran successfully and returned 0
                    } else {
                        System.out.println("2"); // script ran but returned an error code
                    }
                } catch (Exception e) {
                    System.out.println("3"); // error while running the script
                }
            } else {
                System.out.println("4"); // email doesn't exist in the database
            }
        } catch (SQLException | InterruptedException e) {
            System.out.println("5"); // other error, like a connection issue or an invalid query
        }
    }
}