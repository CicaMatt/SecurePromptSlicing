import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.servlet.HandlerInterceptor;

public class AuthenticationInterceptor implements HandlerInterceptor {

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        String user = (String) request.getSession().getAttribute("user");
        String role = (String) request.getSession().getAttribute("role");

        if (user == null) {
            response.sendRedirect(request.getContextPath() + "/login");
            return false;
        } else if ("admin".equals(role)) {
            response.sendRedirect(request.getContextPath() + "/admin");
            return false;
        } else {
            response.sendRedirect(request.getContextPath() + "/user");
            return false;
        }
    }
}