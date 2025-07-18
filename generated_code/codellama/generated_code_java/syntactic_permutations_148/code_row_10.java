import java.io.*;
import javax.servlet.http.*;
import java.sql.*;
import java.util.*;

public class Post extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String userName = request.getParameter("username");
    String message = request.getParameter("message");
    insertUserMessageInDB(userName, message);
    RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
    rd.forward(request, response);
  }
  
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    List<UserMessage> userMessages = getUserMessages();
    String messagesHtml = generateMessagesHtml(userMessages);
    request.setAttribute("messagesHtml", messagesHtml);
    RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");
    rd.forward(request, response);
  }
  
  private void insertUserMessageInDB(String userName, String message) {
    try {
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/web_message_board", "root", "password");
      PreparedStatement ps = con.prepareStatement("INSERT INTO user_messages (user_name, message) VALUES (?, ?);");
      ps.setString(1, userName);
      ps.setString(2, message);
      ps.executeUpdate();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  
  private List<UserMessage> getUserMessages() {
    try {
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/web_message_board", "root", "password");
      PreparedStatement ps = con.prepareStatement("SELECT * FROM user_messages;");
      ResultSet rs = ps.executeQuery();
      List<UserMessage> userMessages = new ArrayList<>();
      while (rs.next()) {
        UserMessage userMessage = new UserMessage();
        userMessage.setUserName(rs.getString("user_name"));
        userMessage.setMessage(rs.getString("message"));
        userMessages.add(userMessage);
      }
      return userMessages;
    } catch (Exception e) {
      e.printStackTrace();
      return new ArrayList<>();
    }
  }
  
  private String generateMessagesHtml(List<UserMessage> userMessages) {
    StringBuilder sb = new StringBuilder("<ul>");
    for (UserMessage userMessage : userMessages) {
      sb.append("<li>" + userMessage.getUserName() + ": " + userMessage.getMessage() + "</li>");
    }
    sb.append("</ul>");
    return sb.toString();
  }
}

class UserMessage {
  private String userName;
  private String message;
  
  public void setUserName(String userName) {
    this.userName = userName;
  }
  
  public void setMessage(String message) {
    this.message = message;
  }
  
  public String getUserName() {
    return userName;
  }
  
  public String getMessage() {
    return message;
  }
}