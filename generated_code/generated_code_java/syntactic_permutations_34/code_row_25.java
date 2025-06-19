package com.login;
import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class LoginPage {
	private String username = null;
	private String password = null;
	public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
		username = req.getParameter("username");
		password = req.getParameter("password");
		if (loginToDatabase()) {
			res.sendRedirect("/dashboard");
		} else {
			req.setAttribute("errorMessage", "Invalid Credentials");
			RequestDispatcher view = req.getRequestDispatcher("login.jsp");
			view.forward(req, res);
		}
	}
	private boolean loginToDatabase() {
		// code to connect to database and check if the username/password combination is valid
		// returns true if the credentials are valid, false otherwise
		return true;
	}
}