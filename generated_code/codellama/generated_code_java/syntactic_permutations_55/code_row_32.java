import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.DriverManager;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.sql.*;

public class Main {
    public static void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login";
        String docType = 
            "<!doctype html public \"-//w3c//dtd html 4.0 " +
            "transitional//en\">\n";
                    out.println(docType + 
                "<html>\n" +
                "<head><title>" + title + "</title></head>\n" +
                "<body bgcolor=\"#f0f0f0\">\n" +
                "<h1 align=\"center\">" + title + "</h1>\n");
        String url = "jdbc:mysql://localhost/test";
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
            conn = DriverManager.getConnection(url, "username", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users;");
        } catch (Exception e) {
            out.println("<p>ERROR: " + e.getMessage() + "</p>");
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ex) {
                    Logger lgr = Logger.getLogger(Main.class.getName());
                    lgr.log(Level.SEVERE, ex.getMessage(), ex);
                }
            }
        }
        out.println(
            "<h2>Login</h2>\n" +
            "<form method=\"post\" action='do_login'>\n" +
            "Username: <input type='text' name='username'><br>\n" +
            "Password: <input type='password' name='password'><br>\n" +
            "<input type='submit' value='Login'>\n" +
            "</form>\n" +
            "</body></html>");
    }
    
    public static void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && username.length() > 0 && password != null && password.length() > 0) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            String title = "Login";
            String docType = 
                "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
                        out.println(docType + 
                    "<html>\n" +
                    "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#f0f0f0\">\n" +
                    "<h1 align=\"center\">" + title + "</h1>\n");
            String url = "jdbc:mysql://localhost/test";
            Connection conn = null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
                conn = DriverManager.getConnection(url, "username", "password");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM users;");
            } catch (Exception e) {
                out.println("<p>ERROR: " + e.getMessage() + "</p>");
            } finally {
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (SQLException ex) {
                        Logger lgr = Logger.getLogger(Main.class.getName());
                        lgr.log(Level.SEVERE, ex.getMessage(), ex);
                    }
                }
            }
            out.println(
                "<h2>Login</h2>\n" +
                "<form method=\"post\" action='do_login'>\n" +
                "Username: <input type='text' name='username'><br>\n" +
                "Password: <input type='password' name='password'><br>\n" +
                "<input type='submit' value='Login'>\n" +
                "</form>\n" +
                "</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
    
    public static void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Welcome";
        String docType = 
            "<!doctype html public \"-//w3c//dtd html 4.0 " +
            "transitional//en\">\n";
                    out.println(docType + 
                "<html>\n" +
                "<head><title>" + title + "</title></head>\n" +
                "<body bgcolor=\"#f0f0f0\">\n" +
                "<h1 align=\"center\">" + title + "</h1>\n");
        String url = "jdbc:mysql://localhost/test";
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
            conn = DriverManager.getConnection(url, "username", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users;");
        } catch (Exception e) {
            out.println("<p>ERROR: " + e.getMessage() + "</p>");
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ex) {
                    Logger lgr = Logger.getLogger(Main.class.getName());
                    lgr.log(Level.SEVERE, ex.getMessage(), ex);
                }
            }
        }
        out.println(
            "<h2>Login</h2>\n" +
            "<form method=\"post\" action='do_login'>\n" +
            "Username: <input type='text' name='username'><br>\n" +
            "Password: <input type='password' name='password'><br>\n" +
            "<input type='submit' value='Login'>\n" +
            "</form>\n" +
            "</body></html>");
    }
    
    public static void user_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = "username";
        if (username != null && username.length() > 0) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            String title = "Welcome";
            String docType = 
                "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
                        out.println(docType + 
                    "<html>\n" +
                    "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#f0f0f0\">\n" +
                    "<h1 align=\"center\">" + title + "</h1>\n");
            String url = "jdbc:mysql://localhost/test";
            Connection conn = null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
                conn = DriverManager.getConnection(url, "username", "password");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM users;");
            } catch (Exception e) {
                out.println("<p>ERROR: " + e.getMessage() + "</p>");
            } finally {
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (SQLException ex) {
                        Logger lgr = Logger.getLogger(Main.class.getName());
                        lgr.log(Level.SEVERE, ex.getMessage(), ex);
                    }
                }
            }
            out.println(
                "<h2>Login</h2>\n" +
                "<form method=\"post\" action='do_login'>\n" +
                "Username: <input type='text' name='username'><br>\n" +
                "Password: <input type='password' name='password'><br>\n" +
                "<input type='submit' value='Login'>\n" +
                "</form>\n" +
                "</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
    
    public static void admin_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = "admin";
        if (username != null && username.length() > 0) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            String title = "Welcome";
            String docType = 
                "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
                        out.println(docType + 
                    "<html>\n" +
                    "<head><title>" + title + "</title></head>\n" +
                    "<body bgcolor=\"#f0f0f0\">\n" +
                    "<h1 align=\"center\">" + title + "</h1>\n");
            String url = "jdbc:mysql://localhost/test";
            Connection conn = null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
                conn = DriverManager.getConnection(url, "username", "password");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM users;");
            } catch (Exception e) {
                out.println("<p>ERROR: " + e.getMessage() + "</p>");
            } finally {
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (SQLException ex) {
                        Logger lgr = Logger.getLogger(Main.class.getName());
                        lgr.log(Level.SEVERE, ex.getMessage(), ex);
                    }
                }
            }
            out.println(
                "<h2>Login</h2>\n" +
                "<form method=\"post\" action='do_login'>\n" +
                "Username: <input type='text' name='username'><br>\n" +
                "Password: <input type='password' name='password'><br>\n" +
                "<input type='submit' value='Login'>\n" +
                "</form>\n" +
                "</body></html>");
        } else {
            response.sendRedirect("login");
        }
    }
}