import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.servlet.HandlerInterceptor;

public class AuthenticationInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        String userRole = (String) request.getSession().getAttribute("userRole");
        
        if (userRole == null || !userRole.equals("admin") && !userRole.equals("user")) {
            response.sendRedirect(request.getContextPath() + "/login");
            return false;
        } else if (userRole.equals("user")) {
            response.sendRedirect(request.getContextPath() + "/user");
            return false;
        } else if (userRole.equals("admin")) {
            response.sendRedirect(request.getContextPath() + "/admin");
            return false;
        }
        
        return true;
    }
}