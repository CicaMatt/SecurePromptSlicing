import java.util.regex.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    public class RegExpExample extends HttpServlet {
      private String regexPattern;
      private Pattern compiledRegex;
      
      public void init(ServletConfig config) {
        super.init(config);
        this.regexPattern = "[a-zA-Z0-9-]+\\." + config.getInitParameter("target");
        this.compiledRegex = Pattern.compile(this.regexPattern);
      }
      
      public void doGet(HttpServletRequest request, HttpServletResponse response) {
        String target = request.getParameter("target");
        Matcher matcher = compiledRegex.matcher(target);
        if (matcher.matches()) {
          response.sendRedirect(target);
        } else {
          response.sendRedirect("/");
        }
      }
    }