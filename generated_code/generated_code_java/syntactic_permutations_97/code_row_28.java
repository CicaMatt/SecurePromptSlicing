import java.security.MessageDigest;

public class Registration {
    private static final String MD5_ALGORITHM = "MD5";

    public void registerUser(String username, String password, String firstName, String lastName, String email) throws Exception {
        // check if the username is already taken
        String query = "SELECT * FROM users WHERE username = ?";
        ResultSet result = Database.executeQuery(query);
        if (result.next()) {
            throw new Exception("The user already exists");
        }

        // insert into database
        MessageDigest md = MessageDigest.getInstance(MD5_ALGORITHM);
        byte[] hashedPasswordBytes = md.digest(password.getBytes());
        String hashedPassword = new String(hashedPasswordBytes, StandardCharsets.UTF_8);

        query = "INSERT INTO users (username, password, firstName, lastName, email) VALUES (?, ?, ?, ?, ?)";
        Database.executeUpdate(query, username, hashedPassword, firstName, lastName, email);
    }
}