import javax.naming.NamingException;
import javax.servlet.http.HttpServletRequest;
import java.util.HashMap;
import java.util.Map;

import com.sun.mail.imap.IMAPFolder;
import com.sun.mail.pop3.POP3Store;

public class MailingList {
    private static final Map<String, String> EMAILS = new HashMap<>();

    public static void unsubscribe(HttpServletRequest request) throws NamingException {
        String email = request.getParameter("email");
        if (!EMAILS.containsKey(email)) {
            return;
        }
        IMAPFolder inbox = (IMAPFolder) EMAILS.get(email);
        POP3Store store = (POP3Store) inbox.getStore();
        inbox.close(false);
        store.close();
        EMAILS.remove(email);
    }
}