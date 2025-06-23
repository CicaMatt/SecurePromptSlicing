import java.sql.*;
import java.util.Scanner; // for getting user input

// create a class that will contain all the code
public class LoginDatabase {
    public static void main(String[] args) throws SQLException { // throw an exception so we can use try-catch blocks
        // connect to database, with name, username and password
        String url = "jdbc:mysql://localhost/mydb";
        Connection conn = DriverManager.getConnection(url, "root", "root");

        // create the SQL query as a variable
        String sql = "INSERT INTO users (name,password) VALUES (?,?)"; // note the ? characters; these are placeholders

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String name = scanner.nextLine(); // get user input for name

        // hash password with SHA-256 algorithm (the most secure at the moment)
        String hashedPassword = org.apache.commons.codec.digest.DigestUtils.sha256Hex(scanner.nextLine());
        System.out.print("Enter password: ");

        // prepare and execute SQL query with placeholders filled in
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, name); // first placeholder is filled with the user input name
        pstmt.setString(2, hashedPassword); // second placeholder is filled with the hashed password
        int result = pstmt.executeUpdate(); // execute the query and get number of rows affected

        System.out.println("You have successfully inserted " + result + " rows into the database");
    }
}