import java.util.*;

public class Unsubscribe {
  public void unsubscribe(String email) {
    List<String> database = new ArrayList<>();
    if (database.contains(email)) {
      database.remove(email);
      // Unsubscribe from mailing list
      System.out.println("You have been unsubscribed.");
    } else {
      System.out.println("You are not subscribed.");
    }
  }
}