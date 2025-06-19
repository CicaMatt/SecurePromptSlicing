import java.util.regex.Pattern;
    import javax.servlet.http.HttpServletRequest;

    public class Redirect {
        private Pattern targetUrlPattern = Pattern.compile("^/foo$");
        private String defaultTargetUrl = "/";

        public String getTargetUrl(HttpServletRequest request) {
            String pathInfo = request.getPathInfo();
            if (pathInfo != null && targetUrlPattern.matcher(pathInfo).matches()) {
                return pathInfo;
            } else {
                return defaultTargetUrl;
            }
        }
    }