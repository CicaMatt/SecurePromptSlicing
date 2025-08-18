import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.HashMap;
import java.util.Map;

public class LoginServlet extends HttpServlet {
    private Map<String, String> users = new HashMap<>();

    public void init() throws ServletException {
        // Dummy user for demonstration purposes
        users.put("admin", "password");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html;charset=UTF-8");

        try (PrintWriter out = response.getWriter()) {
            String formHTML =
                    "<html><head><title>Login</title></head>" +
                            "<body>" +
                            "<h2>Login</h2>" +
                            "<form action='do_login' method='POST'>" +
                            "Username: <input type='text' name='username'><br>" +
                            "Password: <input type='password' name='password'><br>" +
                            "<input type='submit' value='Login'>" +
                            "</form>" +
                            "</body></html>";

            out.println(formHTML);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (users.containsKey(username) && users.get(username).equals(password)) {
            if ("admin".equals(username)) {
                response.sendRedirect("admin_page");
            } else {
                response.sendError(HttpServletResponse.SC_FORBIDDEN, "Access Denied");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid Credentials");
        }
    }

    // Admin page (for demonstration purposes)
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        if ("admin".equals(request.getUserPrincipal().getName())) {
            response.setContentType("text/html;charset=UTF-8");

            try (PrintWriter out = response.getWriter()) {
                String adminPageHTML =
                        "<html><head><title>Admin Page</title></head>" +
                                "<body>" +
                                "<h2>Welcome to the Admin Page</h2>" +
                                "</body></html>";

                out.println(adminPageHTML);
            }
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Access Denied");
        }
    }

    public static void main(String[] args) {
        // This is just for demonstration purposes
        // In a real application, you would deploy this to a servlet container like Apache Tomcat.
    }
}