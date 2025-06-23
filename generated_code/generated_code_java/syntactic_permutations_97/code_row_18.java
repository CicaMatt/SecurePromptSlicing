import java.security.*;
import java.sql.*;
import javax.crypto.*;
import javax.crypto.spec.SecretKeySpec;
public class Register {
  public static void main(String[] args) {
    String username = getUsername(); //get input for the username
    String password = getPassword(); //get input for password
    String firstName = getFirstName(); //get input for first name
    String lastName = getLastName(); //get input for last name
    String email = getEmail(); //get input for email
    boolean userExists = checkUser(username); //check if the username exists in the database
    if (userExists) {
      System.out.println("Username already exists");
    } else {
      String hashedPassword = encryptPassword(password); //hash password
      insertUser(username, hashedPassword, firstName, lastName, email); //insert username and hashed password into the database
      System.out.println("Registration succeeded");
    }
  }
  public static boolean checkUser(String username) {
    String query = "SELECT * FROM Users WHERE Username=?"; //query to select the username from the database
    boolean userExists = false;
    try (Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "root"); PreparedStatement statement = con.prepareStatement(query);) {
      statement.setString(1, username); //set the input for the query
      ResultSet rs = statement.executeQuery(); //execute the query
      if (rs.next()) {
        userExists = true;
      }
    } catch (SQLException e) {
      System.out.println("Could not connect to database");
    }
    return userExists;
  }
  public static void insertUser(String username, String password, String firstName, String lastName, String email) {
    String query = "INSERT INTO Users (Username, Password, FirstName, LastName, Email) VALUES (?, ?, ?, ?, ?)"; //query to insert data into the database
    try (Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "root"); PreparedStatement statement = con.prepareStatement(query);) {
      statement.setString(1, username); //set input for query
      statement.setString(2, password); //set input for query
      statement.setString(3, firstName); //set input for query
      statement.setString(4, lastName); //set input for query
      statement.setString(5, email); //set input for query
      statement.executeUpdate(); //execute the query
    } catch (SQLException e) {
      System.out.println("Could not connect to database");
    }
  }
  public static String getUsername() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter username: ");
    return sc.nextLine(); //get input from user
  }
  public static String getPassword() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter password: ");
    return sc.nextLine(); //get input from user
  }
  public static String getFirstName() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter first name: ");
    return sc.nextLine(); //get input from user
  }
  public static String getLastName() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter last name: ");
    return sc.nextLine(); //get input from user
  }
  public static String getEmail() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter email: ");
    return sc.nextLine(); //get input from user
  }
  public static String encryptPassword(String password) {
    try {
      SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
      char[] passwordArray = password.toCharArray();
      PBEKeySpec spec = new PBEKeySpec(passwordArray, "salt".getBytes(), 1024, 128);
      SecretKey secretKey = factory.generateSecret(spec);
      byte[] encoded = secretKey.getEncoded();
      String hashedPassword = new String(encoded); //hash the password
      return hashedPassword;
    } catch (InvalidKeySpecException e) {
      System.out.println("Could not generate key");
    } catch (NoSuchAlgorithmException e) {
      System.out.println("Could not find algorithm");
    }
  }
}