package com.coderbyte.java;

    import java.io.IOException;
    import java.util.Map;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class Servlet extends HttpServlet {
      protected void doGet(HttpServletRequest request, HttpServletResponse response) 
          throws ServletException, IOException {
        processRequest(request, response);
      }

      protected void doPost(HttpServletRequest request, HttpServletResponse response)
          throws ServletException, IOException {
        processRequest(request, response);
      }

      private void processRequest(HttpServletRequest request, HttpServletResponse response) 
          throws ServletException, IOException {
        String name = "";
        Map<String, String[]> parameters = request.getParameterMap();
        if (parameters != null && !parameters.isEmpty() && parameters.containsKey("name")) {
            name = parameters.get("name")[0];
        }
        response.setContentType("text/html;charset=UTF-8");
        request.setAttribute("name", name);
        request.getRequestDispatcher("index.jsp").forward(request, response);
      }
    }

    package com.coderbyte.java;

    import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class Main extends HttpServlet {
      private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
          throws ServletException, IOException {
          response.sendRedirect("servlet");
        }

      protected void doPost(HttpServletRequest request, HttpServletResponse response)
          throws ServletException, IOException {
          response.sendRedirect("servlet");
        }
    }