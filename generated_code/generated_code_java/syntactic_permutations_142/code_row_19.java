import java.sql.*;

public class Unsubscribe {
  public static void main(String[] args) {
    String email = getEmail();
    unsubscribeFromList(email);
  }
  
  private static String getEmail() {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter your email address:");
    return scanner.nextLine();
  }
  
  private static void unsubscribeFromList(String email) {
    try {
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
      PreparedStatement statement = conn.prepareStatement("DELETE FROM subscribers WHERE email = ?");
      statement.setString(1, email);
      int rowsDeleted = statement.executeUpdate();
      if (rowsDeleted == 0) {
        System.out.println("You are not in the database.");
      } else {
        System.out.println("You have been unsubscribed.");
      }
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
}