import java.sql.*;
public class Register {
    public static void main(String[] args) throws Exception {
        // Connect to database
        Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost/test", "username", "password");
        System.out.println("Connected to the PostgreSQL server successfully.");
        PreparedStatement pst = conn.prepareStatement("INSERT INTO users(name,password) VALUES(?, ?);");
        
        // get username and password from user
        String name = "John";
        String password = "my_password";
        pst.setString(1, name);
        // hash the password before inserting into db
        pst.setString(2, PasswordHash.createHash(password));
        int row = pst.executeUpdate();
        System.out.println("Inserted rows: " + row);
        
        // Close connection
        conn.close();
    }
}