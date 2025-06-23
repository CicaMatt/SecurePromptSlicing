import java.io.*;  

public class Post {
    public static void post(HttpRequest request, HttpResponse response) throws IOException {  
        String username = request.getParameter("username");
        String message = request.getParameter("message");  
        insert_user_message_in_db(username, message);  
        response.sendRedirect("/main");  
    }
    public static void insert_user_message_in_db(String username, String message) {  
        //code to insert user message in database
    }  
}