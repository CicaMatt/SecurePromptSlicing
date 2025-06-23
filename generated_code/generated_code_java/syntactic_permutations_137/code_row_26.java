import javax.servlet.http.*;
    @WebServlet(name = "checkMod", urlPatterns = "/checkMod")
     public class checkMod extends HttpServlet {
         
         private boolean auth_mod(String session) {
             // authenticate the user and return true if they are a moderator, 
             // or false if they aren't
             return false;
         }
     
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String session = request.getParameter("session");
            boolean isModerator = auth_mod(session);
             if (isModerator == true){
                // redirect the user to a page that moderators can access
                    } else {
                        // redirect the user to a page that non-moderators can access
                    }
        }
     }