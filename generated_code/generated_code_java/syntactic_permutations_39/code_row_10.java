package com.mycompany.app;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class Login extends HttpServlet {
      // JDBC driver name and database URL
      static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
      static final String DB_URL = "jdbc:mysql://localhost/mydb";
    
      //  Database credentials
      static final String USER = "username";
      static final String PASS = "password";
    
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<!DOCTYPE html>");
            out.println("<html><head>");
            out.println("<title>Login Page</title></head>");   
            out.println("<body>");
            out.println("<h1>Login Page</h1>");
            out.println("<form action='login' method='post'>");
            out.println("Username:<input type='text' name='username'><br>");
            out.println("Password:<input type='password' name='password'><br>");
            out.println("<input type='submit' value='Login'>");
            out.println("</form>"); 
            out.println("</body></html>");
        }
    
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            String url = "jdbc:mysql://localhost/";
            Connection conn = null;
            Statement stmt = null;
            try{
                //STEP 2: Register JDBC driver
                Class.forName("com.mysql.jdbc.Driver");
    
                // Open a connection
                System.out.println("Connecting to database...");
                conn = DriverManager.getConnection(DB_URL,USER,PASS);
    
                //STEP 4: Execute a query
                System.out.println("Creating statement...");
                stmt = conn.createStatement();
                String sql;
                sql = "SELECT * FROM USERS";
                ResultSet rs = stmt.executeQuery(sql);
    
                //STEP 5: Extract data from result set
                while(rs.next()){
                    //Retrieve by column name
                    String uName = rs.getString("username");
                    if(uName.equals(username)){
                        String pWord = rs.getString("password");
                        if(pWord.equals(password)){
                            out.println("<!DOCTYPE html>");
                            out.println("<html><head>");
                            out.println("<title>Session Page</title></head>");   
                            out.println("<body>");
                            out.println("Welcome "+username+"!");
                            out.println("</body></html>");
                        }else{
                            //RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
                            out.println("<!DOCTYPE html>");
                            out.println("<html><head>");
                            out.println("<title>Login Page</title></head>");   
                            out.println("<body>");
                            out.println("Username or Password is incorrect!");
                            out.println("</body></html>");
                        }
                    }else{
                        //RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
                        out.println("<!DOCTYPE html>");
                        out.println("<html><head>");
                        out.println("<title>Login Page</title></head>");   
                        out.println("<body>");
                        out.println("Username or Password is incorrect!");
                        out.println("</body></html>");
                    }
                }
                rs.close();
            }catch(SQLException se){
                //Handle errors for JDBC
                se.printStackTrace();
            }catch(Exception e){
                //Handle errors for Class.forName
                e.printStackTrace();
            }finally{
                //finally block used to close resources
                try{
                    if(stmt!=null)
                        conn.close();
                }catch(SQLException se){
                }// do nothing
                try{
                    if(conn!=null)
                        conn.close();
                }catch(SQLException se){
                    se.printStackTrace();
                }//end finally try
            }//end try
            out.close();
        }//end doPost
    }//end class Login