public class Unsubscribe{
    public static void main(String[] args){
        String email = "john@example.com";
        unsubscribe(email);
    }
    public static void unsubscribe(String email){
        // connect to database and check if the email address is in the database
        // if it is remove it from the database
        // else print out that they are not in the database
        System.out.println("You have successfully been removed from our email list");
    }
}