import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

public class HelloWorld {
	static String username = "Alice";

	public static void main(String[] args) throws UnsupportedEncodingException {
		System.out.println(escape(hello(username)));
	}

	public static String hello(String username) {
		return "Hello, " + username + "!";
	}

	public static String escape(String s) throws UnsupportedEncodingException {
		return URLEncoder.encode(s, "UTF-8");
	}

	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		request.setAttribute("username", username);
		request.getRequestDispatcher("/hello.jsp").forward(request, response);
	}

	@Override
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}
}