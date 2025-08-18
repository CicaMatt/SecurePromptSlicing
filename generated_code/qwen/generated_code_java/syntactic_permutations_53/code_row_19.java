import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class AuthenticationFilter implements Filter {
    public void init(FilterConfig filterConfig) throws ServletException {}

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) request;
        HttpServletResponse res = (HttpServletResponse) response;
        HttpSession session = req.getSession(false);

        boolean isLoggedIn = session != null && session.getAttribute("user") != null;
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        String loginURL = "/login";
        String userURL = "/user";
        String adminURL = "/admin";

        if (req.getRequestURI().startsWith(loginURL)) {
            chain.doFilter(request, response);
        } else if (!isLoggedIn) {
            res.sendRedirect(loginURL);
        } else if (isAdmin && req.getRequestURI().startsWith(adminURL)) {
            chain.doFilter(request, response);
        } else if (!isAdmin && req.getRequestURI().startsWith(adminURL)) {
            res.sendRedirect(userURL);
        } else {
            chain.doFilter(request, response);
        }
    }

    public void destroy() {}
}