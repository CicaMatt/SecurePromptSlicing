import java.io.*;
    import javax.servlet.*;
    public class LoginServlet extends GenericServlet {
        private String username = null, password = null;
        
        public void init(ServletConfig config) throws ServletException {
            super.init(config);
            if (username == null || password == null) {
                username = config.getInitParameter("username");
                password = config.getInitParameter("password");
            }
        }
        
        public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException {
            doGet(req, res);
        }
        
        public void doGet(ServletRequest req, ServletResponse res) throws ServletException, IOException {
            String cmd = req.getParameter("cmd");
            if (cmd != null && cmd.equals("login")) {
                String username = req.getParameter("username");
                String password = req.getParameter("password");
                if ((this.username == null || this.password == null) && username.equals(this.username) && password.equals(this.password)) {
                    HttpSession session = req.getSession();
                    session.setAttribute("username", username);
                    res.sendRedirect("secret");
                } else {
                    res.sendRedirect("login.html");
                }
            } else if (cmd != null && cmd.equals("logout")) {
                HttpSession session = req.getSession();
                session.removeAttribute("username");
                res.sendRedirect("index.html");
            } else {
                res.setContentType("text/html;charset=UTF-8");
                PrintWriter out = res.getWriter();
                out.println("<!DOCTYPE html>");
                out.println("<html>");
                out.println("<head><title>Login</title></head>");
                out.println("<body>");
                out.println("<h1>Login</h1>");
                out.println("</body>");
                out.println("</html>");
            }
        }
    }