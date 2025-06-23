import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import javax.sql.DataSource;

public class User {
    private DataSource dataSource = null; 
    public void setDataSource(DataSource ds) {
        this.dataSource = ds;
    }
    public boolean registerUser(String username, String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashInBytes = md.digest(password.getBytes(StandardCharsets.UTF_8));
            String sha256hex = bytesToHex(hashInBytes);
            Connection conn = dataSource.getConnection();
            PreparedStatement ps = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            ps.setString(1, username);
            ps.setString(2, sha256hex);
            int rowsInserted = ps.executeUpdate();
            if (rowsInserted != 0) {
                return true;
            }
        } catch (NoSuchAlgorithmException | SQLException e) {
            System.out.println(e.getMessage());
        }
        return false;
    }
    private static String bytesToHex(byte[] hashInBytes) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < hashInBytes.length; i++) {
            sb.append(Integer.toString((hashInBytes[i] & 0xff) + 0x100, 16).substring(1));
        }
        return sb.toString();
    }
}