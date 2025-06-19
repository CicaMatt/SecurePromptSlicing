import javax.servlet.*;
    import java.io.*;
    public class CheckMod extends HttpServlet{
        private String username;
        private String password;
        private String session;
    
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            try (PrintWriter out = response.getWriter()) {
                username = request.getParameter("username");
                password = request.getParameter("password");
                session = request.getParameter("session");
        
                if(auth_mod()){
                    out.print("User is a moderator");
                }else{
                    out.print("User is not a moderator");
                }
            }
        }
    
        public boolean auth_mod(){
            //check if the user is a moderator
            return true;
        }
    }