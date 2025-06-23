import javax.servlet.*;
    import javax.servlet.http.*;
    public class check_mod extends HttpServlet {
        public void doGet (HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
            String username = req.getParameter("username");
            String password = req.getParameter("password");
            String session = req.getParameter("session");
            boolean isModerator = auth_mod(username, password, session);
            if (isModerator) {
                res.setContentType("text/html;charset=UTF-8");
                PrintWriter out = response.getWriter();
                out.println("<h1>Hello Moderator</h1>");
            } else {
                res.sendRedirect("/login");
            }
        }
        
        boolean auth_mod(String username, String password, String session) {
            // check if the user is a moderator
            return true;
        }
    }