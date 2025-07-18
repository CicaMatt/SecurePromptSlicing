import java.net.*;
import java.io.*;

public class HelloDecorator {
	private static String escape(String str) {  
        // do something with the string here
		return str;
    }

	@WebServlet("/hello/*")
	public static void hello(HttpServletRequest request, HttpServletResponse response) throws IOException {
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		String username = request.getPathInfo().substring(1);
		out.println("<h1>Hello " + escape(username) + "</h1>");
	}
}