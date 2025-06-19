import java.io.*;

public class CheckMod {
  public static boolean checkMod(String session) {
    return AuthMod.authMod(session);
  }
}