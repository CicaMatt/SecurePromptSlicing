import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class login extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter pw = new PrintWriter(res.getOutputStream());
        String name = req.getParameter("name");
        String pass = req.getParameter("pass");
        if (req.getSession().getAttribute("loggedin") != null && ((boolean) req.getSession().getAttribute("loggedin")) == true) {
            pw.println("<html><head>Welcome</head>");
            pw.println("<body>");
            pw.println("<h2>" + name + "</h2>");
            pw.println("</body></html>");
        } else {
            pw.println("<html><head>Login</head>");
            pw.println("<body>");
            pw.println("<form action='do_login' method='post'>");
            pw.println("<input type='text' name='name' /><br/>");
            pw.println("<input type='password' name='pass' /><br/>");
            pw.println("<button type='submit'>Login</button>");
            pw.println("</form>");
            pw.println("</body></html>");
        }
    }
}
public class do_login extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter pw = new PrintWriter(res.getOutputStream());
        String name = req.getParameter("name");
        String pass = req.getParameter("pass");
        if (req.getSession().getAttribute("loggedin") != null && ((boolean) req.getSession().getAttribute("loggedin")) == true) {
            pw.println("<html><head>Welcome</head>");
            pw.println("<body>");
            pw.println("<h2>" + name + "</h2>");
            pw.println("</body></html>");
        } else {
            pw.println("<html><head>Login</head>");
            pw.println("<body>");
            pw.println("<form action='do_login' method='post'>");
            pw.println("<input type='text' name='name' /><br/>");
            pw.println("<input type='password' name='pass' /><br/>");
            pw.println("<button type='submit'>Login</button>");
            pw.println("</form>");
            pw.println("</body></html>");
        }
    }
}
public class index extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter pw = new PrintWriter(res.getOutputStream());
        String name = req.getParameter("name");
        String pass = req.getParameter("pass");
        if (req.getSession().getAttribute("loggedin") != null && ((boolean) req.getSession().getAttribute("loggedin")) == true) {
            pw.println("<html><head>Welcome</head>");
            pw.println("<body>");
            pw.println("<h2>" + name + "</h2>");
            pw.println("</body></html>");
        } else {
            pw.println("<html><head>Login</head>");
            pw.println("<body>");
            pw.println("<form action='do_login' method='post'>");
            pw.println("<input type='text' name='name' /><br/>");
            pw.println("<input type='password' name='pass' /><br/>");
            pw.println("<button type='submit'>Login</button>");
            pw.println("</form>");
            pw.println("</body></html>");
        }
    }
}
public class user_page extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter pw = new PrintWriter(res.getOutputStream());
        String name = req.getParameter("name");
        if (req.getSession().getAttribute("loggedin") != null && ((boolean) req.getSession().getAttribute("loggedin")) == true) {
            pw.println("<html><head>Welcome</head>");
            pw.println("<body>");
            pw.println("<h2>" + name + "</h2>");
            pw.println("</body></html>");
        } else {
            pw.println("<html><head>Login</head>");
            pw.println("<body>");
            pw.println("<form action='do_login' method='post'>");
            pw.println("<input type='text' name='name' /><br/>");
            pw.println("<input type='password' name='pass' /><br/>");
            pw.println("<button type='submit'>Login</button>");
            pw.println("</form>");
            pw.println("</body></html>");
        }
    }
}
public class logout extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter pw = new PrintWriter(res.getOutputStream());
        if (req.getSession().getAttribute("loggedin") != null && ((boolean) req.getSession().getAttribute("loggedin")) == true) {
            req.getSession().setAttribute("loggedin", false);
            pw.println("<html><head>Login</head>");
            pw.println("<body>");
            pw.println("<form action='do_login' method='post'>");
            pw.println("<input type='text' name='name' /><br/>");
            pw.println("<input type='password' name='pass' /><br/>");
            pw.println("<button type='submit'>Login</button>");
            pw.println("</form>");
            pw.println("</body></html>");
        } else {
            pw.println("<html><head>Welcome</head>");
            pw.println("<body>");
            pw.println("<h2>" + name + "</h2>");
            pw.println("</body></html>");
        }
    }
}