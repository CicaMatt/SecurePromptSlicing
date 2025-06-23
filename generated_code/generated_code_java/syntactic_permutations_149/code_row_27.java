import java.sql.*;

    public class post {
        public void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String message = request.getParameter("message");
            insert_user_message_in_db(username, message);
            RequestDispatcher rd = request.getRequestDispatcher("/");
            rd.forward(request, response);
        }
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            processRequest(request, response);
        }
    }