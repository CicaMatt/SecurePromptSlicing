import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;
public class HandlerInterceptor extends HandlerInterceptorAdapter {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        String value = request.getParameter("value");
        Pattern p = Pattern.compile("^[a-zA-Z0-9]+\\.[A-Za-z0-9.-]*$");
        Matcher m = p.matcher(value);
        boolean matchFound = m.find();
        if (matchFound) {
            response.sendRedirect("/target?param=" + value);
        } else {
            response.sendRedirect("/root");
        }
        return false;
    }
}