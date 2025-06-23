import java.security.MessageDigest;
    import java.sql.*;

    public class Main {
      
        public static void main(String[] args) {
            try {
                String username = "john";
                String password = "12345678"; // This is the raw password
                String firstName = "John";
                String lastName = "Doe";
                String email = "johndoe@example.com";
            
                MessageDigest md = MessageDigest.getInstance("SHA-256");
                byte[] hashInBytes = md.digest(password.getBytes());
                StringBuilder sb = new StringBuilder();
                for (byte b : hashInBytes) {
                    sb.append(String.format("%02x", b));
                }
                String hashedPassword = sb.toString();
            
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/sampledb",
                        "root", "password");
                Statement stmt = conn.createStatement();
            
                ResultSet rs = stmt.executeQuery("SELECT username FROM users WHERE username='" + username + "'");
                if (rs.next()) {
                    System.out.println("This username already exists.");
                } else {
                    PreparedStatement preparedStmt = conn
                            .prepareStatement("INSERT INTO users (username, password, firstName, lastName, email) VALUES (?, ?, ?, ?, ?)");
                    preparedStmt.setString(1, username);
                    preparedStmt.setString(2, hashedPassword);
                    preparedStmt.setString(3, firstName);
                    preparedStmt.setString(4, lastName);
                    preparedStmt.setString(5, email);
            
                    // execute the java preparedstatement
                    preparedStmt.executeUpdate();
            
                    System.out.println("Registration successful.");
                }
            } catch (Exception e) {
                System.err.println(e);
            }
        }
    }