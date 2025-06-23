import java.io.*;

public class Login {
  public static void main(String[] args) throws IOException {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    System.out.println("Enter your old email address");
    String oldEmail = reader.readLine();

    System.out.println("Enter your new email address");
    String newEmail = reader.readLine();

    System.out.println("Confirm Password: ");
    String password = reader.readLine();

    if (oldEmail.equals(newEmail)) {
      System.out.println("Error: Old and new email addresses must be different");
      return;
    }

    // check if the user is logged in
    if (!isLoggedIn()) {
      System.out.println("User not logged in");
      return;
    }

    // check if the password matches
    if (!passwordMatches(password)) {
      System.out.println("Error: Incorrect Password");
      return;
    }

    changeEmail(oldEmail, newEmail);
  }

  private static boolean isLoggedIn() {
    // simulate login check
    return true;
  }

  private static boolean passwordMatches(String password) {
    // simulate password check
    return true;
  }

  private static void changeEmail(String oldEmail, String newEmail) {
    System.out.println("Changing email from " + oldEmail + " to " + newEmail);
  }
}