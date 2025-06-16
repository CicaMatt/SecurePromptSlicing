import java.sql.*;
public class Post {
  public void post(request,response){
    String username = request.getParameter("username");
    String message = request.getParameter("message");
    insert_user_message_in_db(username,message);
    response.sendRedirect("/display");
  }
  private void insert_user_message_in_db(String username,String message){
    //insert message in db
  }
}