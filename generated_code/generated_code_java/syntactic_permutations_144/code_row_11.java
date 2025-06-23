import java.sql.*;
public class EmailCheck {
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("url", "username", "password");
            PreparedStatement stmt = con.prepareStatement("SELECT email FROM users WHERE email = ? ");
            stmt.setString(1, args[0]);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                Process process = Runtime.getRuntime().exec(args);
                int exitVal = process.waitFor();
                System.out.println(exitVal == 0 ? 1 : 0);
            } else {
                System.out.println(0);
            }
        } catch (Exception e) {
            System.err.println(e);
        }
    }
}