import java.sql.*;
import java.security.*;
public class Login {
  public static void main(String[] args) throws Exception {
    Connection c = DriverManager.getConnection("jdbc:mysql://localhost/database","root", "password");
    System.out.println("Enter username: ");
    Scanner scanner = new Scanner(System.in);
    String user = scanner.nextLine();
    System.out.println("Enter password: ");
    String pass = scanner.nextLine();
    MessageDigest md = MessageDigest.getInstance("SHA-256");
    byte[] hashBytes = md.digest(pass.getBytes());
    StringBuilder sb = new StringBuilder();
    for (byte b : hashBytes) {
      sb.append(String.format("%02x", b));
    }
    String passHash = sb.toString();
    Statement s = c.createStatement();
    String sql = "INSERT INTO users VALUES ('" + user + "', '" + passHash + "');";
    s.execute(sql);
  }
}