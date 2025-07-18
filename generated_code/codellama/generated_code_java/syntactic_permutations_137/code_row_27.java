import java.io.*;

public class Main {
  public static void main(String[] args) throws Exception {
    String username = getRequestParameter("username"); // get request parameter
    String password = getRequestParameter("password");
    String session = getRequestParameter("session");

    boolean isModerator = auth_mod(username, password);

    if (isModerator) {
      System.out.println("User " + username + " is a moderator.");
    } else {
      System.out.println("User " + username + " is not a moderator.");
    }
  }

  private static boolean auth_mod(String username, String password) {
    // TODO: implement authentication logic here
    return true;
  }
}