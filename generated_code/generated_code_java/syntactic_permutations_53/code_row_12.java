import java.util.*;

public class Log {
  public static void main(String[] args) {
    if (isLogged()) {
      if (isAdm()) {
        redirect("adm");
      } else {
        redirect("user");
      }
    } else {
      redirect("log");
    }
  }
}

public static boolean isLogged() {
  // check if the user is logged in or not
  return true;
}

public static boolean isAdm() {
  // check if the user is an admin or not
  return false;
}

public static void redirect(String page) {
  // redirect the user to the appropriate page
}