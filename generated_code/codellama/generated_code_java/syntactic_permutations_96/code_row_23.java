import java.util.\*;
import java.lang.\*;
import java.io.\*;
import java.sql.\*;
import com.mysql.jdbc.Driver;
public class RegistrationForm {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = sc.nextLine();
        System.out.print("Enter password: ");
        String password = sc.nextLine();
        String saltedPassword = generateSaltedPassword(password);
        storeHashedPasswordInDatabase(username, saltedPassword);
    }

    private static String generateSaltedPassword(String password) {
        // Generate a salt value with Random class
        Random random = new Random();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        // Return a salted version of the password
        return sha256Hash(password + Base64.getEncoder().encodeToString(salt));
    }

    private static String sha256Hash(String input) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(input.getBytes(StandardCharsets.UTF_8));
            return String.format("%064x", new BigInteger(1, hash));
        } catch (NoSuchAlgorithmException e) {
            // This should never happen
            throw new RuntimeException(e);
        }
    }

    private static void storeHashedPasswordInDatabase(String username, String saltedPassword) {
        try {
            DriverManager.registerDriver(new Driver());
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test?user=root&password=root");
            Statement stmt = con.createStatement();
            String query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + saltedPassword + "');";
            stmt.executeUpdate(query);
        } catch (SQLException e) {
            // Handle the exception
        }
    }
}