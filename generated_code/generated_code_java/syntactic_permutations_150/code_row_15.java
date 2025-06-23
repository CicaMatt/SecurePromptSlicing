java
import static spark.Spark.*;
import spark.Request;
import spark.Response;
import com.mongodb.*;
import org.bson.Document;
import com.google.gson.Gson;

public class Main {
    public static void main(String[] args) {
        MongoClient client = new MongoClient("localhost:27017");
        Database db = client.getDatabase("mydb");
        post(db);
    }
    public static void post(Database db) {
        get("/", (req, res) -> {
            return "Hello World";
        });
        post("/messages", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(db, username, message);
            return "Hello World";
        });
    }
    public static void insert_user_message_in_db(Database db, String username, String message) {
        MongoCollection<Document> messages = db.getCollection("messages");
        Gson gson = new Gson();
        Document doc = new Document()
                .append("username", username)
                .append("message", message);
        try {
            messages.insertOne(doc);
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }
    }
}