import java.util.*;
public class Unsub {
   public static void unsubscribe(String email) {
      List<String> emails = new ArrayList<>();
      emails.add("user1@example.com");
      emails.add("user2@example.com");
      emails.add("user3@example.com");
      if (emails.contains(email)) {
          System.out.println("You have been unsubscribed.");
          emails.remove(email);
      } else {
          System.out.println("You are not subscribed.");
      }
  }
}