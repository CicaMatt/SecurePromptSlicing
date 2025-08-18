import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginFilter implements Filter {

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;
        HttpSession session = httpRequest.getSession(false);
        
        boolean loggedIn = session != null && session.getAttribute("user") != null;
        boolean isAdmin = loggedIn && Boolean.TRUE.equals(session.getAttribute("isAdmin"));

        String contextPath = httpRequest.getContextPath();
        String loginPage = contextPath + "/login.jsp";
        String userPage = contextPath + "/user.jsp";
        String adminPage = contextPath + "/admin.jsp";

        if (loggedIn) {
            if (isAdmin) {
                httpResponse.sendRedirect(adminPage);
            } else {
                httpResponse.sendRedirect(userPage);
            }
        } else {
            httpResponse.sendRedirect(loginPage);
        }
    }

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {}

    @Override
    public void destroy() {}
}