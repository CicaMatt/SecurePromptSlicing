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

### Explanation:
We import the necessary classes from java.io, java.net, java.util, and java.util.regex packages. We define the target variable as a string that stores the value of the target query parameter and the referer variable as a string that stores the value of the referer header. The pattern object is created using the Pattern class's compile method by passing a regular expression string that matches one or more alphanumeric characters or hyphens followed by a period. We create a matcher object using the pattern object's matcher method and pass the value of the referer variable as an argument. If the matcher object's matches method returns true, we redirect the user to the target url using the response object's sendRedirect method. Otherwise, we redirect the user to the root of the site.