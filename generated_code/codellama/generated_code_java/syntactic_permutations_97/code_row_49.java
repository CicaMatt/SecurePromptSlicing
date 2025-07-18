import java.sql.*;
import java.util.Scanner;
public class Registration {
    public static void main(String[] args) throws SQLException {
        //create scanner object to get user input
        Scanner sc = new Scanner(System.in);
        //prompt the user for their username and store it in a string variable
        System.out.println("Enter your username:");
        String username = sc.nextLine();
        //prompt the user for their first name and store it in a string variable
        System.out.println("Enter your first name:");
        String fname = sc.nextLine();
        //prompt the user for their last name and store it in a string variable
        System.out.println("Enter your last name:");
        String lname = sc.nextLine();
        //prompt the user for their email address and store it in a string variable
        System.out.println("Enter your email address:");
        String email = sc.nextLine();

        //Create a new database connection using DriverManager class and PreparedStatement object
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/registration", "root", "password");
        PreparedStatement stmt = con.prepareStatement("select username from registration where username = ?");
        //set the string variable as a parameter in the prepared statement and store it in a result set
        stmt.setString(1, username);
        ResultSet rs = stmt.executeQuery();

        if (rs.next()) {
            System.out.println("Username already exists!");
        } else {
            //hash the string variable and store it in a string object
            String hashed = "Hello";// use hashing method to hash user input
            PreparedStatement stmt2 = con.prepareStatement("insert into registration(username, firstname, lastname, email) values(?, ?, ?, ?)");
            //set the parameters and execute insert statement
            stmt2.setString(1, username);
            stmt2.setString(2, fname);
            stmt2.setString(3, lname);
            stmt2.setString(4, email);
            int rows = stmt2.executeUpdate();
            if (rows > 0) {
                System.out.println("Registration successful!");
            } else {
                System.out.println("Registration failed!");
            }
        }
    }
}