java
import static spark.Spark.*;
import com.mongodb.MongoClient;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCollection;
import org.bson.Document;
import spark.Request;
import spark.Response;

public class WebApp {
  public static void main(String[] args) {
    port(Integer.valueOf(System.getenv("PORT")));
    MongoClient mongo = new MongoClient();
    MongoDatabase db = mongo.getDatabase("messages");
    String username = "";
    String message = "";
    post("/submit_message", (req, res) -> {
      username = req.queryParams("username");
      message = req.queryParams("message");
      insert_user_message_in_db(username, message, db);
      return "redirect:/";
    });
  }

  private static void insert_user_message_in_db(String username, String message, MongoDatabase db) {
    MongoCollection<Document> messages = db.getCollection("messages");
    Document newMessage = new Document().append("username", username).append("message", message);
    messages.insertOne(newMessage);
  }
}