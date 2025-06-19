import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import org.apache.catalina.connector.Request;
import org.apache.catalina.connector.Response;
import org.apache.tomcat.util.buf.MessageBytes;
public class RedirectModule {
  private Pattern pattern = null;
  private String defaultRedirectUrl = "";
  public RedirectModule(String regex, String redirectUrl) {
    this.pattern = Pattern.compile(regex);
    this.defaultRedirectUrl = redirectUrl;
  }
  public void service(Request request, Response response) {
    String url = getRequestedUrl(request);
    if (pattern.matcher(url).find()) {
      response.sendRedirect(url);
    } else {
      response.sendRedirect(defaultRedirectUrl);
    }
  }
  private String getRequestedUrl(HttpServletRequest request) {
    MessageBytes mb = connector.getMessageBytes();
    String url = null;
    if (mb != null) {
      url = mb.toString();
    } else {
      // handle the case where the url is not encoded in the connector
      url = request.getRequestURI();
    }
    return url;
  }
}