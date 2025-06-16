import java.net.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexRedirect {
   private static final Pattern targetUrlPattern = Pattern.compile("^https://example\\.(com|org)/path/to/resource$");
   private static final String defaultRedirectUrl = "https://www.example.net";

   public static void main(String[] args) throws MalformedURLException {
      URL targetUrl = new URL("https://example.com/path/to/resource");
      URL redirectUrl = getRedirectUrl(targetUrl);
      System.out.println(redirectUrl);
   }

   public static URL getRedirectUrl(URL targetUrl) {
      Matcher matcher = targetUrlPattern.matcher(targetUrl.toString());
      return (matcher.matches()) ? new URL(targetUrl) : new URL(defaultRedirectUrl);
   }
}