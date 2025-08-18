import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class AuthenticationFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {}

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;

        HttpSession session = httpRequest.getSession(false);
        boolean isLoggedIn = session != null && session.getAttribute("user") != null;
        boolean isAdmin = isLoggedIn && Boolean.TRUE.equals(session.getAttribute("isAdmin"));

        if (!isLoggedIn) {
            httpResponse.sendRedirect("/login");
        } else if (isAdmin) {
            httpResponse.sendRedirect("/admin");
        } else {
            httpResponse.sendRedirect("/user");
        }
    }

    @Override
    public void destroy() {}
}