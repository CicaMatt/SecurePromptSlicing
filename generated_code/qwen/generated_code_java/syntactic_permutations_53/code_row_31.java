import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class AuthenticationFilter implements Filter {
    public void init(FilterConfig filterConfig) throws ServletException {}

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;

        HttpSession session = httpRequest.getSession(false);
        boolean loggedIn = session != null && session.getAttribute("user") != null;
        boolean isAdmin = loggedIn && "admin".equals(session.getAttribute("role"));

        String loginURI = httpRequest.getContextPath() + "/login.jsp";
        String userURI = httpRequest.getContextPath() + "/user.jsp";
        String adminURI = httpRequest.getContextPath() + "/admin.jsp";

        if (loggedIn) {
            if (isAdmin) {
                httpResponse.sendRedirect(adminURI);
            } else {
                httpResponse.sendRedirect(userURI);
            }
        } else {
            httpResponse.sendRedirect(loginURI);
        }
    }

    public void destroy() {}
}