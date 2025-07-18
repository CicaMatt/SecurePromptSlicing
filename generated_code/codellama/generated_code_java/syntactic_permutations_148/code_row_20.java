import java.io.*;
import javax.servlet.http.*;

public class PostMessageServlet extends HttpServlet {
	@Override
	public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
	    String username = req.getParameter("username");
		String message = req.getParameter("message");
		insert_user_message_in_db(username, message);
		res.sendRedirect("/main-page.jsp");
	}
	public void insert_user_message_in_db(String username, String message) {
		// Add code to insert the username and message into a database table called "Messages" with columns "Username" and "Message"
	}
}