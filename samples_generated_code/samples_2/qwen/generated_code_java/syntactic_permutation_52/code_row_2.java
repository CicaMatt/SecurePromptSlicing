import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form method='post' action='do_login'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("login?error=1");
        }
    }
}

public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Index Page</h2>");
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }
}

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Secret Settings</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login?error=1");
        }
    }
}

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginFilter implements Filter {
    public void init(FilterConfig filterConfig) throws ServletException {}

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;

        HttpSession session = httpRequest.getSession(false);
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);

        if (!isLoggedIn && !httpRequest.getRequestURI().endsWith("login")
                && !httpRequest.getRequestURI().endsWith("do_login")) {
            httpResponse.sendRedirect(httpRequest.getContextPath() + "/login");
        } else {
            chain.doFilter(request, response);
        }
    }

    public void destroy() {}
}

import javax.servlet.annotation.WebFilter;

@WebFilter(urlPatterns = "/*")
public class FilterInitializer extends LoginFilter {}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServletWrapper extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        new LoginServlet().doGet(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        new LoginServlet().doPost(request, response);
    }
}

@WebServlet("/index")
public class IndexServletWrapper extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        new IndexServlet().doGet(request, response);
    }
}

@WebServlet("/secret")
public class SecretServletWrapper extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        new SecretServlet().doGet(request, response);
    }
}