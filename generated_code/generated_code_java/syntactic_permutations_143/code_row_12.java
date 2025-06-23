import java.util.*;
import java.io.*;
import java.net.*;
import com.mongodb.*;
import com.twilio.sdk.*;

public class Unsubscribe {
  public static void main(String[] args) throws IOException, TwilioRestException {
    // Get the email parameter from the query string
    String email = request.queryParams("email");

    // Create a connection to the MongoDB server
    MongoClient client = new MongoClient();
    DB database = client.getDB("subscriptions");
    DBCollection collection = database.getCollection("emails");

    // Check if the email is in the database
    BasicDBObject query = new BasicDBObject();
    query.put("email", email);

    DBCursor cursor = collection.find(query);
    if (cursor.hasNext()) {
      // Delete the user from the database
      DBObject user = cursor.next();
      ObjectId id = user.get("_id");
      BasicDBObject deleteQuery = new BasicDBObject();
      deleteQuery.put("_id", id);
      collection.remove(deleteQuery);

      // Unsubscribe the user from the mailing list using Twilio
      String accountSid = "ACCOUNT_SID";  // Your Account SID from www.twilio.com/console
      String authToken = "AUTH_TOKEN";   // Your Auth Token from www.twilio.com/console
      TwilioRestClient client = new TwilioRestClient(accountSid, authToken);
      List<NameValuePair> params = new ArrayList<NameValuePair>();
      params.add(new BasicNameValuePair("EmailAddress", email));
      params.add(new BasicNameValuePair("ListName", "newsletter"));
      client.getAccount().getIncomingPhoneNumber("PHONE_NUMBER").delete();
    } else {
      // Return a message saying the user is not subscribed
      response.status(401);
      HashMap<String, String> data = new HashMap<String, String>();
      data.put("message", "Email is not subscribed");
      return new Gson().toJson(data);
    }
  }
}