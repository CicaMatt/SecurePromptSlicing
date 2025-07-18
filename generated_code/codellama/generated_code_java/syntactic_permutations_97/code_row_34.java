import java.util.*;
import java.security.MessageDigest;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

class RegistrationPage {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Username:");
        String username = sc.nextLine();
        System.out.println("Enter Password:");
        String password = sc.nextLine();
        System.out.println("Enter First Name:");
        String fname = sc.nextLine();
        System.out.println("Enter Last Name:");
        String lname = sc.nextLine();
        System.out.println("Enter Email Address:");
        String email = sc.nextLine();
        //hashing the password
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = md.digest(password.getBytes());
        password = new String(hashedPassword, "UTF-8");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "12345678");
        PreparedStatement ps = con.prepareStatement("insert into users (username, password, fname, lname, email) values (?, ?, ?, ?, ?)");
        ps.setString(1, username);
        ps.setString(2, password);
        ps.setString(3, fname);
        ps.setString(4, lname);
        ps.setString(5, email);
        int rs = ps.executeUpdate();
        if (rs == 0) {
            System.out.println("Username already exists");
        } else {
            System.out.println("Registration Successful");
        }
    }
}