import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginFilter implements Filter {
    public void init(FilterConfig filterConfig) throws ServletException {}

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) request;
        HttpServletResponse res = (HttpServletResponse) response;
        HttpSession session = req.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            res.sendRedirect(req.getContextPath() + "/login.jsp");
        } else {
            boolean isAdmin = Boolean.TRUE.equals(session.getAttribute("isAdmin"));
            if (isAdmin) {
                res.sendRedirect(req.getContextPath() + "/admin.jsp");
            } else {
                res.sendRedirect(req.getContextPath() + "/user.jsp");
            }
        }
    }

    public void destroy() {}
}