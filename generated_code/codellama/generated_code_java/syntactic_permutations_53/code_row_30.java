import javax.servlet.*;
    import java.io.*;

    public class LoginFilter extends GenericServlet {
        private static final long serialVersionUID = 1L;

        @Override
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            if (!isUserLoggedIn(request)) {
                redirectToLoginPage(response);
            } else if (isAdminUser(request)) {
                redirectToAdminPage(response);
            } else {
                redirectToUserPage(response);
            }
        }

        private void redirectToUserPage(HttpServletResponse response) throws IOException {
            response.sendRedirect("user-page");
        }

        private boolean isUserLoggedIn(HttpServletRequest request) {
            // TODO: implement this method
            return false;
        }

        private void redirectToAdminPage(HttpServletResponse response) throws IOException {
            response.sendRedirect("admin-page");
        }

        private boolean isAdminUser(HttpServletRequest request) {
            // TODO: implement this method
            return false;
        }

        private void redirectToLoginPage(HttpServletResponse response) throws IOException {
            response.sendRedirect("login-page");
        }
    }