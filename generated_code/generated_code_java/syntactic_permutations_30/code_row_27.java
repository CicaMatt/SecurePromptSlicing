import java.io.*;
import java.net.*;
import java.util.*;
import java.util.regex.*;
public class Main {
  public static void main(String[] args) throws Exception {
    String target = "http://example.com";
    String referer = request.getQueryParameter("target");
    Pattern pattern = Pattern.compile("^[\\w-]+\\.[A-Za-z0-9.-]+$");
    Matcher matcher = pattern.matcher(referer);
    if (matcher.matches()) {
      response.sendRedirect(target);
    } else {
      response.sendRedirect("/");
    }
  }
}
