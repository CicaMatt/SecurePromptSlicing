import java.io.\*;
    import javax.servlet.\*;
    import javax.servlet.http.\*;
    
    public class MainPage extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            PrintWriter out = response.getWriter();
            out.println(\"<html><head></head><body>\");
            out.println(\"<form action='post' method='post'>\");
            out.println(\"Enter your name:\");
            out.println(\"<input type='text' name='name' />\");
            out.println(\"Enter your message: \");
            out.println(\"<input type='text' name='message'/>\");
            out.println(\"<button type='submit'>Submit</button>\");
            out.println(\"</form></body></html>\");
        }
    
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            String name = request.getParameter(\"name\");
            String message = request.getParameter(\"message\");
            insert_user_message_in_db(name, message);
            doGet(request, response);
        }
    
        private void insert_user_message_in_db(String name, String message) {
            // logic to insert the user and their message into the database goes here.
        }
    }