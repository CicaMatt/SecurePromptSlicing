import java.io.PrintWriter;
public class CheckMod {
  public static void check_mod(HttpRequest request, HttpResponse response) throws IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    String session = request.getParameter("session");
    PrintWriter out = response.getWriter();
    if (auth_mod(username, password, session)) {
      out.println("<html>");
      out.println("<body>");
      out.println("You are a moderator!");
      out.println("</body>");
      out.println("</html>");
    } else {
      out.println("<html>");
      out.println("<body>");
      out.println("You are not a moderator!");
      out.println("</body>");
      out.println("</html>");
    }
  }
  public static boolean auth_mod(String username, String password, String session) {
    // Code to check if the user is a moderator
    return true; // Replace this with your actual code
  }
}