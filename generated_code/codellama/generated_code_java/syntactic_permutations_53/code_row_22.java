package com.mycompany.mavenproject1;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class LoginController {
    
    public static String loginPage(HttpServletRequest request, HttpServletResponse response) {
        return "login.jsp";
    }
    
    public static String userPage(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession();
        if (session.getAttribute("username") != null) {
            return "user_page.jsp";
        } else {
            return "login.jsp";
        }
    }
    
    public static String adminPage(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession();
        if (session.getAttribute("username") != null && session.getAttribute("admin") == true) {
            return "admin_page.jsp";
        } else {
            return "login.jsp";
        }
    }
}