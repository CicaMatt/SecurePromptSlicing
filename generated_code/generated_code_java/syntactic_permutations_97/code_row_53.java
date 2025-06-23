import java.security.MessageDigest;
import java.sql.*;
import javax.xml.bind.DatatypeConverter;

public class Registration {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost/";
    //  Database credentials
    private static final String USER = "root";
    private static final String PASS = "root";

    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement preparedStatement = null;
        try {
            //STEP 1: Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");
            // STEP 2: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            //STEP 3: Execute a query
            String username = "username";
            String password = "password";
            String firstName = "firstname";
            String lastName = "lastname";
            String email = "email@example.com";
            String saltedPassword = generateSaltedPassword(password);
            preparedStatement = conn
                    .prepareStatement("SELECT * from user where username=?");
            preparedStatement.setString(1, username);
            ResultSet rs = preparedStatement.executeQuery();
            if (rs.next()) {
                System.out.println("Username already exists");
                return;
            } else {
                preparedStatement = conn
                        .prepareStatement("INSERT INTO user VALUES(?,?,?,?,?)");
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, saltedPassword);
                preparedStatement.setString(3, firstName);
                preparedStatement.setString(4, lastName);
                preparedStatement.setString(5, email);
                // execute insert SQL stetement
                preparedStatement.executeUpdate();
                System.out.println("Registration succeeded");
            }
        } catch (SQLException se) {
            //Handle errors for JDBC
            se.printStackTrace();
        } catch (Exception e) {
            //Handle errors for Class.forName
            e.printStackTrace();
        } finally {
            //finally block used to close resources
            try {
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
            } catch (SQLException se2) {
            }// nothing we can do
            try {
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException se) {
                se.printStackTrace();
            } //end finally try
        } //end try
        System.out.println("Goodbye!");
    }

    private static String generateSaltedPassword(String password) throws Exception {
        byte[] salt = new byte[16];
        String saltAsHex = DatatypeConverter.printHexBinary(salt);
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        String hashedPasswordAsHex = DatatypeConverter.printHexBinary(hashedPassword);
        return saltAsHex + hashedPasswordAsHex;
    }
}