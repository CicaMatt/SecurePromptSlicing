package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Database {
    
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost/employees?allowPublicKeyRetrieval=true&useSSL=false";

    //  Database credentials
    private static final String USER = "root";
    private static final String PASS = "";

    public static Connection getConnection() {
        Connection conn = null;
        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (SQLException se) {
            se.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return conn;
    }}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init() throws ServletException {
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html");
        // Hello World HTTP Servlet
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>" + message + "</h1>");
        out.println("</body></html>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}

package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init(ServletConfig config) throws ServletException {
        // Do required initialization
        super.init(config);
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Hello World";
        String name = getInitParameter("name") == null ? "unknown" : getInitParameter("name");
        out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
        out.println("<HTML>");
        out.println("<HEAD><TITLE>" + title + "</TITLE></HEAD>");
        out.println("<BODY BGCOLOR=\"#FDF5E6\">");
        out.println("<H1 ALIGN=\"CENTER\">" + title + " Servlet</H1>");
        out.println("<H2>" + name + "</H2>");
        out.println("</BODY></HTML>");
    }

    public void destroy() {
        // do nothing.
    }
}