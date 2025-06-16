public class Unsubscribe{
        public static void unsubscribe(String email){
            Database db = new Database();
            if (db.checkEmail(email)){
                db.removeEmail(email);
                System.out.println("You have been unsubscribed");
            }else{
                System.out.println("This email is not in the database");
            }
        }
    }