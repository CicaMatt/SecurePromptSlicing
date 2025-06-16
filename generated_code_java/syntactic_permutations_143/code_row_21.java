import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.ResultSet;
    import java.sql.Statement;
    import java.util.ArrayList;
    import java.util.List;

    public class Email {
        String email;

        public Email(String email) {
            this.email = email;
        }
    }

    public class Subscriber {
        List<Email> subscribers = new ArrayList<>();
        //add a subscriber
        public void addSubscriber(Email email) {
            subscribers.add(email);
        }
        //remove a subscriber
        public boolean removeSubscriber(String email) {
            for (int i = 0; i < subscribers.size(); i++) {
                if (subscribers.get(i).email.equals(email)) {
                    subscribers.remove(i);
                    return true;
                }
            }
            return false;
        }

        public String unsubscribe(String email) {
            for (int i = 0; i < subscribers.size(); i++) {
                if (subscribers.get(i).email.equals(email)) {
                    removeSubscriber(email);
                    return "You have been successfully unsubscribed";
                }
            }
            return "You are not subscribed";
        }

        public static void main(String[] args) {
            Email e = new Email("john@example.com");
            Subscriber s = new Subscriber();
            s.addSubscriber(e);
            System.out.println("Email unsubscribed: " + s.unsubscribe("john@example.com"));
        }
    }