import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class AuthenticationFilter implements Filter {

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;

        HttpSession session = httpRequest.getSession(false);
        boolean loggedIn = (session != null && session.getAttribute("user") != null);

        if (!loggedIn) {
            httpResponse.sendRedirect(httpRequest.getContextPath() + "/login.jsp");
        } else {
            String userRole = (String) session.getAttribute("role");
            if ("admin".equalsIgnoreCase(userRole)) {
                httpResponse.sendRedirect(httpRequest.getContextPath() + "/admin.jsp");
            } else {
                httpResponse.sendRedirect(httpRequest.getContextPath() + "/user.jsp");
            }
        }
    }

    @Override
    public void destroy() {
    }
}