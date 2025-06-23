import java.sql.*;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.Mac;
import org.apache.commons.codec.binary.Hex;
import static java.lang.System.out;

public class Register {
    public static void main(String[] args) {
        // JDBC driver name and database URL
        String jdbcDriver = "com.mysql.jdbc.Driver";
        String dbUrl = "jdbc:mysql://localhost/user_table";

        // Database credentials
        String user = "root";
        String password = "";

        try {
            Class.forName(jdbcDriver);
            Connection conn = DriverManager.getConnection(dbUrl, user, password);
            Statement stmt = conn.createStatement();
            ResultSet rs;

            // get username, first name, last name, email and password from user input
            Scanner scanner = new Scanner(System.in);
            out.println("Enter username:");
            String username = scanner.nextLine();
            out.println("Enter first name:");
            String fname = scanner.nextLine();
            out.println("Enter last name:");
            String lname = scanner.nextLine();
            out.println("Enter email address:");
            String email = scanner.nextLine();
            out.println("Enter password:");
            String pwd = scanner.nextLine();

            // hash the user's password using SHA-256
            SecretKeySpec secretKey = new SecretKeySpec("mySecureKey".getBytes(), "HmacSHA256");
            Mac sha256_HMAC = Mac.getInstance("HmacSHA256");
            sha256_HMAC.init(secretKey);
            String hashedPwd = Hex.encodeHexString(sha256_HMAC.doFinal(pwd.getBytes()));

            // check if username is already in database
            rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "'");

            if (rs.next()) {
                out.println("Username already exists! Please try another one.");
            } else {
                // insert new user into database
                String sql = "INSERT INTO users (username, hashed_pwd, first_name, last_name, email) VALUES ('" + username + "', '" + hashedPwd + "', '" + fname + "', '" + lname + "', '" + email + "')";
                stmt.executeUpdate(sql);

                out.println("Registration successful!");
            }
        } catch (Exception e) {
            System.err.println("Got an exception! ");
            System.err.println(e.getMessage());
        }
    }
}