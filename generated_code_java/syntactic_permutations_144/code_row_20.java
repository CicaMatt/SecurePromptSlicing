import java.util.*; 

    public class CheckEmail {
        private static int check(String email) { 
            // Check database for email 
            if (email == null || !database.contains(email)) return 0; 
            else unsubscribeEmail(email); 
            return 1; 
        } 

        public static void main(String[] args) {
            int result = check("john@example.com");
            System.out.println(result);
        }
    }