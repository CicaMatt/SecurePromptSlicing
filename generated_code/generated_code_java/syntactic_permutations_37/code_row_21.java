import java.io.*;
    import java.util.*;

    // Database
    class User {
      private String username;
      private String password;
      public User(String username, String password) {
        this.username = username;
        this.password = password;
      }
      public String getUsername() { return username; }
      public String getPassword() { return password; }
    }

    // UI
    class LoginPage {
      private String errorMessage;
      private final List<User> users;
      public LoginPage(List<User> users) {
        this.users = users;
      }
      public String login() {
        boolean userValidated = false;
        for (User u: users) {
          if (username.equals(u.getUsername()) && password.equals(u.getPassword())) {
            return "redirect:/success";
          }
        }
        return "cant_login";
      }
    }