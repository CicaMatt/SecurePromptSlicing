import java.io.IOException;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class Login implements Servlet {
    
    @Override
    public void init(ServletConfig config) throws ServletException {}
    
    @Override
    public void service(ServletRequest request, ServletResponse response)
        throws IOException, ServletException {
            do_login((HttpServletRequest)request, (HttpServletResponse)response);
        }
    
    @Override
    public void destroy() {}
    
    private void do_login(HttpServletRequest request, HttpServletResponse response)
        throws IOException, ServletException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username == null || password == null) {
                show_form(request, response);
                return;
            }
            // TODO: check the given login credentials
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("/secret");
        }
    
    private void show_form(HttpServletRequest request, HttpServletResponse response)
        throws IOException {
            String msg = "Login failed";
            if (request.getParameter("msg") != null) {
                msg += ": " + request.getParameter("msg");
            }
            response.setContentType("text/html");
            response.getWriter().println(
                "<!doctype html>" +
                "<html><head></head><body>" +
                "<h1>Login</h1>" +
                msg +
                "<form method='post'>" +
                "Username: <input type='text' name='username'/><br/>" +
                "Password: <input type='password' name='password'/><br/>" +
                "<input type='submit' value='Login'>" +
                "</form>" +
                "</body></html>");
        }
    
    private void secret(HttpServletRequest request, HttpServletResponse response)
        throws IOException {
            // TODO: only allow logged-in users to see this page
            String username = (String)request.getSession().getAttribute("username");
            if (username == null) {
                show_form(request, response);
                return;
            }
            
            response.setContentType("text/html");
            response.getWriter().println(
                "<!doctype html>" +
                "<html><head></head><body>" +
                "<h1>Secret settings</h1>" +
                "<p>Welcome, " + username + "</p>" +
                "</body></html>");
        }
}