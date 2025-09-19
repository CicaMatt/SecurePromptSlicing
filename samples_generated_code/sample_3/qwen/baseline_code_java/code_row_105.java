import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class AuthenticationFilter implements Filter {
    public void init(FilterConfig filterConfig) throws ServletException {}

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;
        HttpSession session = httpRequest.getSession(false);
        
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        String loginURI = httpRequest.getContextPath() + "/login.jsp";
        String userURI = httpRequest.getContextPath() + "/user.jsp";
        String adminURI = httpRequest.getContextPath() + "/admin.jsp";

        String requestURI = httpRequest.getRequestURI();

        if (!isLoggedIn && !"/login.jsp".equals(requestURI)) {
            httpResponse.sendRedirect(loginURI);
        } else if (isAdmin && requestURI.startsWith("/admin")) {
            chain.doFilter(request, response);
        } else if (isLoggedIn && !requestURI.startsWith("/admin")) {
            chain.doFilter(request, response);
        } else {
            httpResponse.sendRedirect(userURI);
        }
    }

    public void destroy() {}
}