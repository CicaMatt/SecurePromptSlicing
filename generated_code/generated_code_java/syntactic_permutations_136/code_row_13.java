import java.io.*;
import java.util.*;

public class CheckMod {
  public static String check_mod(String username, String password) {
    if (username.equals("admin") && password.equals("password")) {
      return "true";
    } else {
      return "false";
    }
  }
}