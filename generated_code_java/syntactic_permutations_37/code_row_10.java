package LoginPage;

import java.util.*;
import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServlet;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;

public class LoginPage extends HttpServlet {
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		if (username == null || password == null) {
			response.sendRedirect("/login?error=true");
		} else if (!username.equals("admin") && !password.equals("password")) {
			response.sendRedirect("/cant_login");
		} else {
			Cookie cookie = new Cookie("loggedIn", "true");
			cookie.setMaxAge(60 * 3);
			response.addCookie(cookie);
			response.sendRedirect("/success");
		}
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.getRequestDispatcher("loginPage.jsp").forward(request, response);
	}
}