import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;
import com.google.appengine.api.mail.MailService;
import com.google.appengine.api.mail.MailServiceFactory;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Email parameter is required.");
            return;
        }

        DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
        Query query = new Query("SubscribedUsers").setFilter(new Query.FilterPredicate("email", Query.FilterOperator.EQUAL, email));
        Entity userEntity = datastore.prepare(query).asSingleEntity();

        if (userEntity != null) {
            Key userKey = userEntity.getKey();
            datastore.delete(userKey);

            unsubscribeFromMailingList(email);
            
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("You have been successfully unsubscribed.");
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            response.getWriter().write("The email is not subscribed.");
        }
    }

    private void unsubscribeFromMailingList(String email) throws IOException {
        MailService mailService = MailServiceFactory.getMailService();
        
        // Assuming the mailing list system provides a method to unsubscribe
        // Here, we just print as a placeholder for actual unsubscription logic
        System.out.println("Unsubscribing " + email);
    }
}