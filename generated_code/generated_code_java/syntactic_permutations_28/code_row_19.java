import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.apache.commons.lang3.StringUtils;
import javax.servlet.*;
import javax.servlet.http.*;

public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private String regexpTargetUrl = "/default/target";
    private Pattern patternTargetUrl;
    
    public void init() {
        // Compile the regular expression when the module is loaded.
        String regexp = getServletConfig().getInitParameter("regexp");
        if (StringUtils.isBlank(regexp)) {
            throw new IllegalArgumentException("Missing required init param 'regexp'");
        }
        patternTargetUrl = Pattern.compile(regexp);
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String targetUrl = getRedirectTarget(request);
        
        // Set the redirect URL and status code.
        response.sendRedirect(targetUrl);
    }
    
    private String getRedirectTarget(HttpServletRequest request) {
        // Use the regular expression to match the target URL.
        Matcher matcher = patternTargetUrl.matcher(request.getRequestURI());
        if (matcher.find()) {
            return matcher.group();
        } else {
            return regexpTargetUrl;
        }
    }
}