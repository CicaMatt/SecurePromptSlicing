import java.util.Scanner; 
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class AuthenticationFilter extends HttpServlet {
        private static final String LOGIN_PAGE = "/login";
        private static final String USER_PAGE = "/user";
        private static final String ADMIN_PAGE = "/admin";
    
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            // Check if session is valid and redirect user appropriately
            HttpSession session = request.getSession(false);
            String username = (String)session.getAttribute("username");
            boolean admin = (boolean)session.getAttribute("admin");
    
            if (username == null || !session.isNew()) {
                response.sendRedirect(LOGIN_PAGE);
            } else if (admin) {
                response.sendRedirect(ADMIN_PAGE);
            } else {
                response.sendRedirect(USER_PAGE);
            }
        }
    
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            // Check if login credentials are valid and update session accordingly
            String username = request.getParameter("username");
            String password = request.getParameter("password");
    
            boolean isValidUser = verifyLoginCredentials(username, password);
            if (isValidUser) {
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                session.setAttribute("admin", false);
            } else {
                response.sendRedirect(LOGIN_PAGE);
            }
        }
    
        private boolean verifyLoginCredentials(String username, String password) {
            // Check if username and password are valid (e.g., by checking a database)
            return true;
        }
    }