import java.util.*;

public class Main {
  public static void main(String[] args) {
    String username = getUserInput();
    String password = getPasswordInput();
    User user = new User(username, password);
    login(user);
  }

  private static String getUserInput() {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter username: ");
    return scanner.nextLine();
  }
  
  private static String getPasswordInput() {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter password: ");
    return scanner.nextLine();
  }

  private static void login(User user) {
    Database database = new Database();
    if (database.usernameExists(user.getUsername())) {
      if (database.checkPasswordCorrect(user)) {
        redirectToHomePage(user);
      } else {
        System.out.println("Incorrect password.");
      }
    } else {
      System.out.println("Username does not exist.");
    }
  }
  
  private static void redirectToHomePage(User user) {
    HomePage homePage = new HomePage();
    homePage.displayWelcomeMessage(user);
  }
}

class User {
  private String username;
  private String password;
  
  public User(String username, String password) {
    this.username = username;
    this.password = password;
  }
  
  public String getUsername() {
    return username;
  }
  
  public String getPassword() {
    return password;
  }
}

class Database {
  private Map<String, String> users;
  
  public Database() {
    users = new HashMap<>();
    // Add some sample data to the database.
    users.put("johndoe", "password123");
    users.put("janedoe", "pass$1234");
    users.put("mrrobot", "password111");
  }
  
  public boolean usernameExists(String username) {
    return users.containsKey(username);
  }
  
  public boolean checkPasswordCorrect(User user) {
    String password = users.get(user.getUsername());
    if (password != null) {
      return password.equals(user.getPassword());
    }
    return false;
  }
}

class HomePage {
  public void displayWelcomeMessage(User user) {
    System.out.println("Welcome, " + user.getUsername() + "!");
  }
}