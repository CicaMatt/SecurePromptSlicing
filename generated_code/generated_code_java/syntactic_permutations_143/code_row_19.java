package com.example;
import java.util.*;

public class Unsubscribe {
  public static void main(String[] args) {
    String email = "someone@example.com";

    if (isSubscribed(email)) {
      unsubscribeFromMailingList(email);
      deleteUserFromDatabase(email);
    } else {
      System.out.println("You are not subscribed to the mailing list.");
    }
  }

  private static boolean isSubscribed(String email) {
    // check if email is in the database
    return true;
  }

  private static void unsubscribeFromMailingList(String email) {
    // remove email from the mailing list
    System.out.println("You have been removed from our mailing list.");
  }

  private static void deleteUserFromDatabase(String email) {
    // delete email from the database
  }
}