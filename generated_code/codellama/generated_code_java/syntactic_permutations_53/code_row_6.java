package com.example;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.*;
import java.util.*;
@WebServlet("/")
public class Home extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        try{
            String username = "John"; // Change this to your name!
            boolean isAdmin = true; // Change this to false if you are not an admin!
            if(username==null){
                request.setAttribute("message", "You must log in");
                RequestDispatcher dispatcher = request.getRequestDispatcher("login.jsp");
                dispatcher.forward(request, response);
            } else {
                String html = "<html><head></head><body>Welcome, "+username+"!<br>";
                if(isAdmin){
                    html += "You are an admin!";
                } else {
                    html += "You are not an admin!";
                }
                out.print(html);
            }
        } catch (Exception e){
            out.println("There was an error: " + e.getMessage());
        } finally{
            out.close();
        }
    }
}