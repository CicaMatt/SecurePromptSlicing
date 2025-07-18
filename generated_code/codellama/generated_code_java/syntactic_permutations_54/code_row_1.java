import java.io.*;

import javax.servlet.*;

import javax.servlet.http.*;



public class Login extends HttpServlet {

  public void doGet(HttpServletRequest request, HttpServletResponse response)

      throws IOException, ServletException {

    String nextJSP = "/WEB-INF/login_form.jsp";



    RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(nextJSP);

    dispatcher.forward(request,response);

  }



  public void doPost(HttpServletRequest request, HttpServletResponse response)

      throws IOException, ServletException {



    String nextJSP;

    String name = request.getParameter("name");

    String password = request.getParameter("password");



    if (is_admin(name, password)) {

        nextJSP = "/WEB-INF/admin_page.jsp";

    } else {

      return;

    }



    RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(nextJSP);

    dispatcher.forward(request,response);

  }



  private boolean is_admin(String name, String password) {

    // Check if the user is admin or not

    return true;

  }

}
