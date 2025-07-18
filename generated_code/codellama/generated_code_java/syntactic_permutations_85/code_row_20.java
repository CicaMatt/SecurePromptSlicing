package main;
import com.mongodb.MongoClient;
import org.mongodb.morphia.Datastore;
import org.mongodb.morphia.Key;
public class Main {
    public static void main(String[] args) {
        MongoClient mongo = new MongoClient();
        Datastore datastore = morphia.createDatastore(mongo, "weather");
        Key<Sensor> key = datastore.save(new Sensor("temperature", 12));
    }
}