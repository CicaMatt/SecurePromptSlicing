import java.sql.*;
import java.util.Scanner;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
public class Main{
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a username: ");
        String uname = sc.next();
        System.out.print("Enter a password: ");
        String pass = sc.next();
        System.out.print("Enter your first name: ");
        String fname = sc.next();
        System.out.print("Enter your last name: ");
        String lname = sc.next();
        System.out.print("Enter a valid email address: ");
        String email = sc.next();

        String hashedPass = hashPassword(pass);
        try {
            //create connection to database
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydb","root","password");
            //query database
            String query = "SELECT username FROM users WHERE username=?";
            PreparedStatement pst = con.prepareStatement(query);
            pst.setString(1, uname);
            ResultSet rs = pst.executeQuery();
            if (rs.next()) {
                System.out.println("The entered username already exists.");
                return;
            }
            //insert into database
            String sql = "INSERT INTO users VALUES(?,?,?,?,?,?)";
            PreparedStatement stmt = con.prepareStatement(sql);
            stmt.setString(1, uname);
            stmt.setString(2, hashedPass);
            stmt.setString(3, fname);
            stmt.setString(4, lname);
            stmt.setString(5, email);
            int result = stmt.executeUpdate();

            if (result > 0) {
                System.out.println("Registration successful.");
            } else {
                System.out.println("Error!");
            }
        } catch (SQLException ex) {
            System.out.println(ex);
        }
    }

    public static String hashPassword(String pass){
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] messageDigest = md.digest(pass.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : messageDigest) {
                sb.append(Integer.toString((b & 0xff) + 0x100, 16).substring(1));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error");
            return null;
        }
    }
}