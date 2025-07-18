package com.example.webapp;
    
    import java.io.IOException;
    import java.util.HashMap;
    import java.util.Map;
    
    public class WebApp {
        private static Map<String, String> users = new HashMap<>();
        
        public static void do_login(HttpRequest request) throws IOException {
            String username = request.getFormParameter("username");
            String password = request.getFormParameter("password");
            
            if (users.containsKey(username)) {
                String storedPassword = users.get(username);
                
                if (storedPassword.equals(password)) {
                    request.getSession().setUsername(username);
                    request.getResponse().redirect("/secret");
                } else {
                    request.getResponse().sendError(401, "Invalid username or password.");
                }
            } else {
                request.getResponse().sendError(401, "Invalid username or password.");
            }
        }
        
        public static void index(HttpRequest request) throws IOException {
            request.getResponse().setContentType("text/html");
            request.getResponse().setStatus(200);
            
            String html = "" +
                    "<!DOCTYPE html>\n" +
                    "<html>\n" +
                    "  <head>\n" +
                    "    <meta charset=\"utf-8\">\n" +
                    "    <title>WebApp</title>\n" +
                    "  </head>\n" +
                    "  <body>\n" +
                    "    <h1>WebApp</h1>\n" +
                    "    <a href=\"/login\">Login</a>\n" +
                    "  </body>\n" +
                    "</html>";
            
            request.getResponse().send(html);
        }
        
        public static void login(HttpRequest request) throws IOException {
            request.getResponse().setContentType("text/html");
            request.getResponse().setStatus(200);
            
            String html = "" +
                    "<!DOCTYPE html>\n" +
                    "<html>\n" +
                    "  <head>\n" +
                    "    <meta charset=\"utf-8\">\n" +
                    "    <title>WebApp</title>\n" +
                    "  </head>\n" +
                    "  <body>\n" +
                    "    <h1>Login</h1>\n" +
                    "    <form action=\"/do_login\" method=\"post\">\n" +
                    "      <label for=\"username\">Username:</label>\n" +
                    "      <input type=\"text\" id=\"username\" name=\"username\"><br><br>\n" +
                    "      <label for=\"password\">Password:</label>\n" +
                    "      <input type=\"password\" id=\"password\" name=\"password\"><br><br>\n" +
                    "      <input type=\"submit\" value=\"Login\">\n" +
                    "    </form>\n" +
                    "  </body>\n" +
                    "</html>";
            
            request.getResponse().send(html);
        }
        
        public static void secret(HttpRequest request) throws IOException {
            String username = request.getSession().getUsername();
            
            if (username != null) {
                request.getResponse().setContentType("text/plain");
                request.getResponse().setStatus(200);
                
                String secret = "Hello, " + username + ". This is a secret page.";
                
                request.getResponse().send(secret);
            } else {
                request.getResponse().redirect("/login");
            }
        }
    }