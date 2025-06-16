import java.util.*;
public class Unsubscribe {
private String email;
private String dbConnection;
public Unsubscribe(String email) {
this.email = email;
}
public void checkDB() {
// Check if the email exists in the database
if(!dbExists(email)) {
return;
} else {
unsubscribe();
}
}
private boolean dbExists(String email) {
// Connect to DB and execute query
// return false or true depending on result
return true;
}
public void unsubscribe() {
// Call script that unsubscribes the email
if(!scriptReturns1()) {
System.out.println("Failed to unsubscribe");
} else {
System.out.println("Unsubscribed");
}
}
private boolean scriptReturns1() {
// Run script that unsubscribes the email
return true;
}
public static void main(String[] args) {
new Unsubscribe("someone@example.com").checkDB();
}
}