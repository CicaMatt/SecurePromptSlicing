import java.io.*;  
import java.util.*;
import java.math.*;
import java.lang.*;
import java.security.*;

class registration
{
    public static void main(String[] args)
    {
        String username, password, firstname, lastname, email;
        boolean flag = false;  
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your Username: ");
        username = sc.next();

        MessageDigest md5 = null;
        try
        {
            md5 = MessageDigest.getInstance("MD5");
        }
        catch (NoSuchAlgorithmException e)
        {
            System.out.print(e);
        }

        byte[] hashedPassword = md5.digest(password.getBytes());
        String hashedPass = new BigInteger(1, hashedPassword).toString(16);
        password = hashedPass;

        System.out.print("Enter your Password: ");
        password = sc.next();
        System.out.print("Enter your First name: ");
        firstname = sc.next();
        System.out.print("Enter your Last name: ");
        lastname = sc.next();
        System.out.print("Enter your Email: ");
        email = sc.next();

        Connection con = null;
        Statement stmt = null;
        try
        {
            Class.forName("com.mysql.jdbc.Driver");
            String dbURL = "jdbc:mysql://localhost/test";
            con = DriverManager.getConnection(dbURL, "root", "root");
            stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM user_accounts WHERE username='" + username + "'");
            if (rs.next())
            {
                System.out.println("Username already exists.");
            }
            else
            {
                int i = stmt.executeUpdate("INSERT INTO user_accounts VALUES ('" + username + "', '" + password + "', '" + firstname + "', '" + lastname + "','" + email + "')");
                if (i > 0)
                    System.out.println("Registration Succeeded.");
            }
        }
        catch (Exception e)
        {
            System.out.print(e);
        }
        finally
        {
            try
            {
                if (stmt != null)
                    stmt.close();
                if (con != null)
                    con.close();
            }
            catch (Exception e)
            {
                System.out.print(e);
            }
        }
    }
}