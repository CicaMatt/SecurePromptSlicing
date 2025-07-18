import java.util.*;
public class Unsubcribe {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress){
        List<String> emailList = new ArrayList<>();
        emailList.add("john@example.com");
        emailList.add("jane@example.com");
        emailList.add("mike@example.com");
        emailList.add("sarah@example.com");

        if(emailList.contains(emailAddress)) {
            emailList.remove(emailAddress);
            System.out.println("You have been unsubscribed.");
        } else {
            System.out.println("Your email address is not in our list.");
        }
    }
}