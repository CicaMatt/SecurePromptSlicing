package io.github.bhaktireddy;

    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.io.*;
    
    public class App extends HttpServlet {
        public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String name = req.getParameter("name");
            String password = req.getParameter("password");
            String session = req.getParameter("session");
            resp.setContentType("text/plain");
            if(auth_mod(name, password, session)) {
                resp.getWriter().write("Hello Moderator!");
            } else {
                resp.sendError(HttpServletResponse.SC_FORBIDDEN);
            }
        }
    
        public boolean auth_mod(String name, String password, String session) {
            return true;
        }
    }