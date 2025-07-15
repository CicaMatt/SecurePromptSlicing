import java.io.*; import javax.servlet.*; import javax.servlet.http.*;



public class Post extends HttpServlet {

   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

      String name = request.getParameter("name");

      String message = request.getParameter("message");



      insert_user_message_in_db(name, message);



      RequestDispatcher rd = request.getRequestDispatcher("index.html");

      rd.include(request, response);

   }

}
