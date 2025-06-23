package com.codewithshuvro;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class Login extends HttpServlet {
    	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
            //read form data
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            //connect to database
            Connection con=null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                con = DriverManager.getConnection("jdbc:mysql://localhost/test", "username", "password");

                String query = "select * from users where username='"+username+"' and password= '"+password+"'";
                Statement stmt = con.createStatement();
                ResultSet rs = stmt.executeQuery(query);

                if(rs.next()){
                    request.setAttribute("message", "Login successfully");
                    RequestDispatcher rd = request.getRequestDispatcher("dashboard.jsp");
                    rd.forward(request, response);
                } else {
                    request.setAttribute("message", "Username and Password are invalid.");
                    RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
                    rd.include(request, response);
                }
            } catch (Exception e){
                e.printStackTrace();
            } finally {
                if(con != null) {
                    try{
                        con.close();
                    }catch(SQLException se){
                        se.printStackTrace();
                    }
                }
            }
    	}
    }