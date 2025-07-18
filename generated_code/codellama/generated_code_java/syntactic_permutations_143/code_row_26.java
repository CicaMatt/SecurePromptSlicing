// package name
    package com.company;
    
    // import dependencies
    import com.mongodb.client.*;
    import com.mongodb.client.model.*;
    import org.bson.Document;
    import javax.servlet.annotation.*;
    import javax.servlet.http.*;
    import java.io.IOException;
    
    @WebServlet(name = "Unsubscribe", urlPatterns = "/unsubscribe")
    public class Unsubscribe extends HttpServlet {
        // method for handling GET requests to the /unsubscribe endpoint
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            // get email parameter from query string
            String email = request.getParameter("email");
    
            // create new MongoClient
            MongoClient mongoClient = MongoClients.create();
            // connect to MongoDB and get handle to database
            MongoDatabase database = mongoClient.getDatabase("email-db");
            // get a handle to the collection
            MongoCollection<Document> collection = database.getCollection("emails");
    
            // check if email is in database
            Document result = collection.find(Filters.eq("email", email)).first();
            if (result == null) {
                response.setStatus(401);
                response.getWriter().println("You are not subscribed");
            } else {
                // delete from database
                collection.deleteOne(new Document("email", email));
    
                // unsubscribe from mailing list
                Mailchimp.unsubscribe(email);
    
                // send success message back to user
                response.setStatus(200);
                response.getWriter().println("Successfully unsubscribed");
            }
        }
    }