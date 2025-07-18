import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Random;

public class UserService {
    private static final String hashAlgo = "SHA-256"; // the hashing algorithm to be used

    /**
     * Inserts a user into the database. The password is hashed using a salt.
     * 
     * @param username - the username of the user
     * @param password - the password of the user
     * @throws SQLException if an error occurs while inserting to the database
     */
    public static void createUser(String username, String password) throws SQLException {
        byte[] salt = generateSalt(); // generate a new salt for this user
        byte[] hashedPassword = hashPassword(password, salt); // hash the given password using the salt
        
        // prepare an insert statement to insert into the database
        try (Connection conn = getConnection(); 
             PreparedStatement ps = conn.prepareStatement("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)")) {
            ps.setString(1, username); // set parameters of the prepared statement
            ps.setBytes(2, salt);
            ps.setBytes(3, hashedPassword);
            ps.executeUpdate(); // insert into the database
        }
    }
    
    /**
     * Generates a random salt for hashing a password.
     * 
     * @return a byte[] containing the salt
     */
    private static byte[] generateSalt() {
        Random rng = new SecureRandom(); // use a secure RNG to generate the salt
        byte[] salt = new byte[16]; // salt will be 16 bytes long
        rng.nextBytes(salt); // fill the salt with random data
        return salt;
    }
    
    /**
     * Hashes a password using a given salt.
     * 
     * @param password - the password to hash
     * @param salt - the salt to use for hashing
     * @return a byte[] containing the hashed password
     */
    private static byte[] hashPassword(String password, byte[] salt) {
        MessageDigest digest; // object used to perform the hashing
        
        try {
            digest = MessageDigest.getInstance(hashAlgo); // get a new instance of the hashing algorithm
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Hashing algorithm not found: " + hashAlgo, e); // should never happen
        }
        
        digest.reset(); // reset the digest object to its initial state
        digest.update(salt); // update the digest with the salt
        return digest.digest(password.getBytes()); // hash the password using the salt
    }
}