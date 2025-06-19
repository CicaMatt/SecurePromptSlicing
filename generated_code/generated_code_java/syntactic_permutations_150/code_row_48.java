import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Main extends HttpServlet {
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String username = request.getParameter("username");
		String message = request.getParameter("message");
		insert_user_message_in_db(username, message);
	}

	public void insert_user_message_in_db(String username, String message) {
		// establish connection to the database and insert a new record with the 
		// given username and message. You can use any database library you prefer.

	}
}