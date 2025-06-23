import spark.Spark;
import static spark.Spark.*;

import com.mongodb.BasicDBObject;
import com.mongodb.MongoClient;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

public class App {
    public static void main(String[] args) {
        MongoClient mongoClient = new MongoClient("localhost", 27017);
        MongoDatabase database = mongoClient.getDatabase("chat_app");
        MongoCollection<Document> collection = database.getCollection("messages");
        
        port(8080);
        
        get("/", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            
            if(!username.isEmpty() && !message.isEmpty()) {
                BasicDBObject document = new BasicDBObject();
                document.put("username", username);
                document.put("message", message);
                
                collection.insertOne(document);
            }
            
            String output = "";
            FindIterable<Document> documents = collection.find();
            for(Document doc : documents) {
                output += doc.toJson() + "<br/>";
            }
            
            return output;
        });
        
        post("/", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            
            if(!username.isEmpty() && !message.isEmpty()) {
                BasicDBObject document = new BasicDBObject();
                document.put("username", username);
                document.put("message", message);
                
                collection.insertOne(document);
            }
            
            res.redirect("/");
            return null;
        });
    }
}