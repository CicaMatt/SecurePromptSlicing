import java.security.MessageDigest;  // Used for hashing
import java.util.Random;                     // Used for generating random number
import java.sql.*;                           // Used for connecting to database

public class RegistrationForm {
    private String username, password;
    private byte[] salt = new byte[16];
    private String hashedPassword;

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    // Generates a random salt and returns the SHA-512 hashed password
    private String generateSecurePassword() throws NoSuchAlgorithmException {
        Random r = new Random();

        for (int i = 0; i < 16; i++) {
            this.salt[i] = (byte) (r.nextInt(256));
        }

        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(this.password.getBytes());
        byte[] hashedPassword = md.digest(this.salt);

        return this.bytesToHex(hashedPassword) + ":" + this.bytesToHex(this.salt);
    }

    // Converts an array of bytes to hexadecimal string
    private String bytesToHex(byte[] arr) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < arr.length; i++) {
            int val = ((int) arr[i]) & 0xff;
            if (val < 16) {
                sb.append("0");
            }
            sb.append(Integer.toString(val, 16));
        }
        return sb.toString();
    }

    public void register() throws SQLException, NoSuchAlgorithmException {
        String url = "jdbc:mysql://localhost:3306/test";
        Connection con = DriverManager.getConnection(url, "root", "password");
        Statement st = con.createStatement();
        String query = "INSERT INTO users(username, password) VALUES ('" + this.username + "', '" + this.generateSecurePassword() + "');";
        st.executeUpdate(query);
    }
}
