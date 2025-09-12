import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("index.html");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}

// index.html
// <!DOCTYPE html>
// <html>
// <head>
//     <title>Message Board</title>
// </head>
// <body>
//     <h1>Submit a Message</h1>
//     <form action="post" method="post">
//         Username: <input type="text" name="username"><br><br>
//         Message: <textarea name="message"></textarea><br><br>
//         <input type="submit" value="Submit">
//     </form>
// </body>
// </html>