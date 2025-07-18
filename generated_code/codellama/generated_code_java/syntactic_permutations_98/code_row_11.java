import java.sql.*;

public class Register {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost/mydatabase";

    public void register(String username, String password) throws SQLException, NoSuchAlgorithmException {
        Connection conn = DriverManager.getConnection(DB_URL, "root", "password");
        PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
        stmt.setString(1, username);
        MessageDigest md5 = MessageDigest.getInstance("MD5");
        byte[] digest = md5.digest(password.getBytes());
        String hashedPassword = new BigInteger(1, digest).toString(16);
        stmt.setString(2, hashedPassword);
        stmt.executeUpdate();
        conn.close();
    }
}