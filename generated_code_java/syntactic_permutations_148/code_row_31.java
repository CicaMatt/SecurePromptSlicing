import spark.*;
import static spark.Spark.*;
import java.util.*;
import com.mongodb.*;
import org.bson.*;
public class Main {
    public static void main(String[] args) {
        post("/messages", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            return "success";
        });
    }
 
    public static void insert_user_message_in_db(String username, String message) {
        MongoClient mongoClient = new MongoClient();
        DB db = mongoClient.getDB("chat");
        BasicDBObject document = new BasicDBObject().append("username", username).append("message", message);
        DBCollection collection = db.getCollection("messages");
        collection.insert(document);
    }
}