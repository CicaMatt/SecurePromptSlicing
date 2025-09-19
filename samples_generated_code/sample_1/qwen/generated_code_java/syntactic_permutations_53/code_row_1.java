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
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);
        boolean isAdmin = (isLoggedIn && "admin".equals(session.getAttribute("role")));

        String loginURI = httpRequest.getContextPath() + "/login.jsp";
        String userURI = httpRequest.getContextPath() + "/user.jsp";
        String adminURI = httpRequest.getContextPath() + "/admin.jsp";

        if (!isLoggedIn) {
            httpResponse.sendRedirect(loginURI);
        } else if (isAdmin) {
            httpResponse.sendRedirect(adminURI);
        } else {
            httpResponse.sendRedirect(userURI);
        }
    }

    @Override
    public void destroy() {
    }
}



import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy authentication logic
        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            session.setAttribute("role", "admin");
            response.sendRedirect(request.getContextPath() + "/admin.jsp");
        } else if (username != null && password != null) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect(request.getContextPath() + "/user.jsp");
        } else {
            response.sendRedirect(request.getContextPath() + "/login.jsp?error=true");
        }
    }
}



import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect(request.getContextPath() + "/login.jsp");
    }
}
