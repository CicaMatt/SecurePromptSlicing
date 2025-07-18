import java.sql.*;
public class Register {
    public static void main(String[] args) {
        try {
            // Create connection to database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/register", "root", "password");

            Statement stmt = conn.createStatement();
            ResultSet rs;

            // get username and password from user input
            Scanner input = new Scanner(System.in);
            System.out.print("Enter a username: ");
            String username = input.nextLine();
            System.out.print("Enter a password: ");
            String password = input.nextLine();

            // hash the password
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.update(password.getBytes());
            byte[] digest = md.digest();
            StringBuilder sb = new StringBuilder();
            for (byte b : digest) {
                sb.append(String.format("%02x", b & 0xff));
            }

            // Insert username and hashed password into database
            String sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + sb.toString() + "')";
            stmt.executeUpdate(sql);
            System.out.println("User successfully registered!");
            conn.close();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}