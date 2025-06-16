import java.sql.*;
  import java.util.ArrayList;
  
  public class Post {
       private String username,message;
       
       // getters and setters
      public void setUsername(String username) { this.username = username; }
      public String getUsername() { return username; }
      public void setMessage(String message) { this.message = message; }
      public String getMessage() { return message; }
      
      // constructor
      public Post(String username, String message) {
          this.username = username;
          this.message = message;
      }
      
      public void insert_user_message_in_db() throws SQLException{
           Connection dbConnection = null;
           PreparedStatement statement = null;
            try{ 
                 String connectionUrl="jdbc:mysql://localhost/message_board";
                dbConnection=DriverManager.getConnection(connectionUrl,"root","");
                String insertQuery = "INSERT INTO messages (username, message) VALUES (?,?)";
                statement = dbConnection.prepareStatement(insertQuery);
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
           } catch(SQLException ex){
                  System.out.println("Error: " + ex.getMessage());
            } finally{
                 if (statement != null) {
                      statement.close();
                    }
               if (dbConnection != null) {
                   dbConnection.close();
                }
          }
       }
      public void post() throws SQLException, IOException {
           insert_user_message_in_db();
           RequestDispatcher dispatcher = request.getRequestDispatcher("/index.jsp");
           dispatcher.forward(request, response);
      }
      
    // display messages  
     public ArrayList<Post> getMessages() throws SQLException{
          Connection dbConnection = null;
          Statement statement = null;
          ResultSet resultSet=null;
          ArrayList<Post> posts = new ArrayList<Post>();
           try { 
                 String connectionUrl="jdbc:mysql://localhost/message_board";
                dbConnection = DriverManager.getConnection(connectionUrl,"root","");
                statement = dbConnection.createStatement();
                resultSet = statement.executeQuery("SELECT * FROM messages");
            while (resultSet.next()) {
                 String username = resultSet.getString("username");
                  String message = resultSet.getString("message");
                   posts.add(new Post(username, message));
               }
          } catch(SQLException ex){
                System.out.println("Error: " + ex.getMessage());
            } finally{
                 if (statement != null) {
                      statement.close();
                    }
               if (dbConnection != null) {
                   dbConnection.close();
                } 
           }
         return posts;
       }
     }