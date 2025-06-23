import java.io.*;
import static spark.Spark.*;
import spark.Request;
import spark.Response;
import spark.Route;
import com.mongodb.MongoClient;
import com.mongodb.client.FindIterable;
import org.bson.Document;
import org.bson.types.ObjectId;
import java.util.ArrayList;
import java.util.List;
import static spark.Spark.*;
import static spark.Spark.get;

public class App {
    public static void main(String[] args) {
        port(Integer.valueOf(System.getenv("PORT")));
        get("/api/temperature_for_location", (req, res) -> temperature_for_location(req));
    }

    public static String temperature_for_location(Request req) {
        MongoClient client = new MongoClient();
        FindIterable<Document> iterable = client.getDatabase("sensor").getCollection("temperature")
            .find(new Document().append("latitude", req.queryParams("latitude"))
                .append("longitude", req.queryParams("longitude"))
                .append("date", req.queryParams("date")));
        String temperature = "0";
        for (Document doc : iterable) {
            temperature = doc.getString("temperature");
        }
        return temperature;
    }
}