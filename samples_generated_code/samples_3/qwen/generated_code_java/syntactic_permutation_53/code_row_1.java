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
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        if (!isLoggedIn) {
            httpResponse.sendRedirect(httpRequest.getContextPath() + "/login.jsp");
        } else if (isAdmin) {
            httpResponse.sendRedirect(httpRequest.getContextPath() + "/admin.jsp");
        } else {
            httpResponse.sendRedirect(httpRequest.getContextPath() + "/user.jsp");
        }
    }

    @Override
    public void destroy() {}
}