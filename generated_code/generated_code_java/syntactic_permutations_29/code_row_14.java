import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.servlet.http.*;
public class RedirectServlet extends HttpServlet { 

     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException { 
        String target = request.getParameter("target"); 
        Pattern p = Pattern.compile(".*example\\.com.*"); 
        Matcher m = p.matcher(target); 
        if (m.matches()) { 
            response.sendRedirect("/success"); 
        } else { 
            response.sendRedirect("/failure"); 
        } 
    } 
}