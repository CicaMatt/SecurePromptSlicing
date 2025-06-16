import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class CheckMod extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            String session = request.getParameter("session");
            if (auth_mod(username, password, session)) {
                response.setStatus(HttpServletResponse.SC_OK);
                response.setContentType("text/html;charset=UTF-8");
                PrintWriter out = response.getWriter();
                out.println("<!DOCTYPE html>");
                out.println("<html>");
                out.println("<head>");
                out.println("<title>Authenticated</title>");              
                out.println("</head>");
                out.println("<body>");
                out.println("<h1>Authenticated</h1>");
                out.println("</body>");
                out.println("</html>");
            } else {
                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            }
        }

        public boolean auth_mod(String username, String password, String session) {
            // check if the user is a moderator
            return true;
        }
    }