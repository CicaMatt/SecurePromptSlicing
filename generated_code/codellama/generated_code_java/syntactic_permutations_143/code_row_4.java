package main;
    
    import com.mongodb.MongoClient;
    import com.mongodb.client.MongoCollection;
    import com.mongodb.client.MongoDatabase;
    import org.bson.Document;
    
    public class Unsubscribe {
        public static void main(String[] args) {
            MongoClient mongoClient = new MongoClient("localhost", 27017);
            MongoDatabase database = mongoClient.getDatabase("users");
            MongoCollection<Document> collection = database.getCollection("subscribers");
    
            // get email parameter from GET request
            String email = "user@example.com";
            
            Document document = new Document();
            document.append("email", email);
    
            if(collection.findOneAndDelete(document) != null){
                System.out.println("User unsubscribed");
            } else {
                System.out.println("User is not subscribed");
            }
        }
    }