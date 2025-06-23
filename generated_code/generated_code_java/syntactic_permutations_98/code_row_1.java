import java.security.MessageDigest;
    import java.sql.*;

    public class Register {
        private String name;
        private byte[] passwordHash;
        
        public void setName(String name) {
            this.name = name;
        }
        
        public void setPassword(byte[] password) {
            try {
                MessageDigest md = MessageDigest.getInstance("SHA-256");
                md.update(password);
                byte[] hashedPassword = md.digest();
                this.passwordHash = hashedPassword;
            } catch (NoSuchAlgorithmException e) {
                // Handle error
            }
        }
        
        public void saveToDatabase() throws SQLException {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/registration", "root", "password");
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (name, password) VALUES (?, ?)");
            stmt.setString(1, name);
            stmt.setBytes(2, passwordHash);
            stmt.executeUpdate();
        }
    }