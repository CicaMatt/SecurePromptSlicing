import java.sql.*;
    import javax.crypto.spec.PBEKeySpec;
    import javax.crypto.SecretKeyFactory;
    import org.apache.commons.codec.binary.Hex;

    public class Registration {
      private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
      private static final String DATABASE_URL = "jdbc:mysql://localhost/mydb";

      private static final byte[] SALT = { (byte) 0xde, (byte) 0x33, (byte) 0x10, (byte) 0x12,
          (byte) 0xde, (byte) 0x33, (byte) 0x10, (byte) 0x12 };

      public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
          // Register JDBC driver
          Class.forName("com.mysql.jdbc.Driver");

          // Open a connection
          System.out.println("Connecting to database...");
          conn = DriverManager.getConnection(DATABASE_URL);

          // SQL statement for creating a new user
          String sql = "INSERT INTO users (username, password) VALUES (?, ?)";

          pstmt = conn.prepareStatement(sql);

          // Set username and password parameters
          Scanner scanner = new Scanner(System.in);
          System.out.print("Enter username: ");
          String username = scanner.nextLine();
          System.out.print("Enter password: ");
          String password = scanner.nextLine();
          pstmt.setString(1, username);
          pstmt.setString(2, hashPassword(password));

          // Execute SQL statement
          int count = pstmt.executeUpdate();
          System.out.println("Registered " + count + " user(s) successfully.");
        } catch (SQLException e) {
          throw new RuntimeException("SQL error occurred:", e);
        } finally {
          // Close resources
          try {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
          } catch (SQLException e) {
            throw new RuntimeException("Error occurred while closing database resources:", e);
          }
        }
      }

      private static String hashPassword(String password) throws Exception {
        PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), SALT, 65536, 128);
        SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        byte[] hash = factory.generateSecret(spec).getEncoded();

        return Hex.encodeHexString(hash);
      }
    }