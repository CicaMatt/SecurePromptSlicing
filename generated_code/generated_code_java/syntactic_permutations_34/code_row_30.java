package com.example;

    import java.util.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class LoginController {
        private static Map<String, String> credentials = new HashMap<>();
    
        public static void init(Map<String, Object> ctx) {
            if (!credentials.isEmpty()) return;
            credentials.put("admin", "password");
            credentials.put("user1", "password1");
        }
        
        public static String login(HttpServletRequest request, HttpServletResponse response) throws Exception {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (credentials.containsKey(username)) {
                String actualPassword = credentials.get(username);
                if (actualPassword != null && actualPassword.equals(password)) {
                    request.setAttribute("user", username);
                    return "dashboard";
                }
            }
            return "login";
        }
    
        public static String logout(HttpServletRequest request, HttpServletResponse response) throws Exception {
            request.getSession().invalidate();
            return "login";
        }
    }