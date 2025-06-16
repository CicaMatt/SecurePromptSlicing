import java.util.*;
    import java.io.*;
    import java.net.*;
    
    class LoginPage {
      public static void main(String[] args) throws Exception {
        ServerSocket ss = new ServerSocket(80);
        
        while (true) {
          Socket s = ss.accept();
          
          PrintWriter out = new PrintWriter(s.getOutputStream(), true);
          BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
          
          String input = in.readLine();
          System.out.println("Input: " + input);
          
          if (input != null) {
            String[] tokens = input.split(" ");
            
            if (tokens[0].equals("POST")) {
              String username = tokens[1];
              String password = tokens[2];
              
              out.println("HTTP/1.1 302 Found");
              out.println("Location: http://localhost:8080/homepage");
            } else if (tokens[0].equals("GET")) {
              out.println("<html>");
              out.println("<head>");
              out.println("<title>Login</title>");
              out.println("</head>");
              out.println("<body>");
              out.println("<form action=\"http://localhost:8080/login\" method=\"POST\">");
              out.println("<label for=\"username\">Username:</label><br>");
              out.println("<input type=\"text\" id=\"username\" name=\"username\"><br>");
              out.println("<label for=\"password\">Password:</label><br>");
              out.println("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
              out.println("<input type=\"submit\" value=\"Login\">");
              out.println("</form>");
              out.println("</body>");
              out.println("</html>");
            }
          }
          
          s.close();
        }
      }
    }
    
    class Login {
      public static void main(String[] args) throws Exception {
        ServerSocket ss = new ServerSocket(8080);
        
        while (true) {
          Socket s = ss.accept();
          
          PrintWriter out = new PrintWriter(s.getOutputStream(), true);
          BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
          
          String input = in.readLine();
          System.out.println("Input: " + input);
          
          if (input != null) {
            String[] tokens = input.split(" ");
            
            if (tokens[0].equals("POST")) {
              String username = tokens[1];
              String password = tokens[2];
              
              Database db = new Database();
              
              if (db.checkUser(username, password)) {
                out.println("HTTP/1.1 302 Found");
                out.println("Location: http://localhost:8080/homepage");
              } else {
                out.println("HTTP/1.1 403 Forbidden");
                out.println("Content-Type: text/html; charset=UTF-8");
                out.println("<html>");
                out.println("<head>");
                out.println("<title>Access Denied</title>");
                out.println("</head>");
                out.println("<body>");
                out.println("<h1>Access Denied</h1>");
                out.println("</body>");
                out.println("</html>");
              }
            } else if (tokens[0].equals("GET")) {
              String redirectUrl = tokens[4];
              
              out.println("HTTP/1.1 302 Found");
              out.println("Location: " + redirectUrl);
            }
          }
          
          s.close();
        }
      }
    }
    
    class Database {
      public boolean checkUser(String username, String password) {
        // Check if the username and password exists in the database
        return true;
      }
    }