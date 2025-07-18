import java.util.*;

public class EmailChange {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter old email: ");
    String oldEmail = scanner.nextLine();
    System.out.println("Enter new email: ");
    String newEmail = scanner.nextLine();
    System.out.println("Enter confirm password: ");
    String confirmPassword = scanner.nextLine();

    if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.isEmpty()) {
      System.out.println("Error: please provide all required information");
      return;
    }

    User user = findUserByEmail(oldEmail);
    if (user == null) {
      System.out.println("Error: no user found with the old email address");
      return;
    }

    if (!user.checkPassword(confirmPassword)) {
      System.out.println("Error: incorrect password provided");
      return;
    }

    User duplicateUser = findUserByEmail(newEmail);
    if (duplicateUser != null) {
      System.out.println("Error: a user with the new email address already exists");
      return;
    }

    user.setEmail(newEmail);
    updateUserInDatabase(user);
    System.out.println("Email changed successfully!");
  }

  private static User findUserByEmail(String email) {
    // query database for user with email and return the first result or null if not found
  }

  private static void updateUserInDatabase(User user) {
    // save changes to database
  }
}

class User {
  private String email;
  private String password;

  public User(String email, String password) {
    this.email = email;
    this.password = password;
  }

  public void setEmail(String newEmail) {
    // check if new email is valid and update the user's email
  }

  public boolean checkPassword(String password) {
    return this.password.equals(password);
  }
}